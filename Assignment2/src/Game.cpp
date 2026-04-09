#include "Game.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include "Components.hpp"
#include "EntityManager.hpp"
#include "Vec2.hpp"

// NOTE: Public:

Game::Game(const std::string &config) {
	init(config);
}

Game::~Game(void) {
	if (m_text)
		delete m_text;
}

void Game::run(void) {
	// TODO: add pause functionality
	// Some systems should function while paused (rendering)
	// Some systems shouldn't (movement / input)
	while (m_running) {
		if (m_player->isActive() == false)
			reset();
		m_entities.update();

		if (!m_paused) {
			sEnemySpawner();
			sMovement();
			sCollision();
		}
		sUserInput();
		sRender();

		// NOTE: increment the current frame
		//  may need to be moved when pause implemented
		++m_currentFrame;
	}
	m_window.close();
}

void Game::init(const std::string &path) {
	std::ifstream fin(path);

	std::string label;
	fin >> label >> m_windowConfig.size.x >> m_windowConfig.size.y >>
		m_windowConfig.framelimit >> m_windowConfig.fullscreen;
	if (m_windowConfig.fullscreen) {
		m_windowState = sf::State::Fullscreen;
	} else {
		m_windowState = sf::State::Windowed;
	}
	std::cout << "WINDOW CONFIG:\n";
	std::cout << m_windowConfig.size.x << std::endl;
	std::cout << m_windowConfig.size.y << std::endl;
	std::cout << m_windowConfig.framelimit << std::endl;
	std::cout << m_windowConfig.fullscreen << std::endl;
	std::cout << "\n";

	m_window.create(sf::VideoMode(m_windowConfig.size), "Geometry Wars",
					sf::Style::Default, m_windowState);
	m_window.setFramerateLimit(m_windowConfig.framelimit);

	fin >> label >> m_fontConfig.path >> m_fontConfig.size >>
		m_fontConfig.colorR >> m_fontConfig.colorG >> m_fontConfig.colorB;
	m_fontColor = sf::Color(static_cast<uint8_t>(m_fontConfig.colorR),
							static_cast<uint8_t>(m_fontConfig.colorG),
							static_cast<uint8_t>(m_fontConfig.colorB));
	std::cout << "FONT CONFIG:\n";
	std::cout << m_fontConfig.path << std::endl;
	std::cout << m_fontConfig.size << std::endl;
	std::cout << (int)m_fontColor.r << std::endl;
	std::cout << (int)m_fontColor.g << std::endl;
	std::cout << (int)m_fontColor.b << std::endl;
	std::cout << "\n";

	// Do this for all structs
	fin >> label >> m_playerConfig.SR >> m_playerConfig.CR >>
		m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >>
		m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >>
		m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
	std::cout << "PLAYER CONFIG:\n";
	std::cout << m_playerConfig.SR << std::endl;
	std::cout << m_playerConfig.CR << std::endl;
	std::cout << m_playerConfig.S << std::endl;
	std::cout << m_playerConfig.FR << std::endl;
	std::cout << m_playerConfig.FG << std::endl;
	std::cout << m_playerConfig.FB << std::endl;
	std::cout << m_playerConfig.OR << std::endl;
	std::cout << m_playerConfig.OG << std::endl;
	std::cout << m_playerConfig.OB << std::endl;
	std::cout << m_playerConfig.OT << std::endl;
	std::cout << m_playerConfig.V << std::endl;

	fin >> label >> m_enemyConfig.SR >> m_enemyConfig.CR >>
		m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >>
		m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >>
		m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >>
		m_enemyConfig.SP;
	std::cout << "ENEMY CONFIG:\n";
	std::cout << m_enemyConfig.SR << std::endl;
	std::cout << m_enemyConfig.CR << std::endl;
	std::cout << m_enemyConfig.SMIN << std::endl;
	std::cout << m_enemyConfig.SMAX << std::endl;
	std::cout << m_enemyConfig.OR << std::endl;
	std::cout << m_enemyConfig.OG << std::endl;
	std::cout << m_enemyConfig.OB << std::endl;
	std::cout << m_enemyConfig.OT << std::endl;
	std::cout << m_enemyConfig.VMIN << std::endl;
	std::cout << m_enemyConfig.VMAX << std::endl;
	std::cout << m_enemyConfig.L << std::endl;
	std::cout << m_enemyConfig.SP << std::endl;
	std::cout << "\n";

	std::cout << "BULLET CONFIG:\n";
	fin >> label >> m_BulletConfig.SR >> m_BulletConfig.CR >>
		m_BulletConfig.S >> m_BulletConfig.FR >> m_BulletConfig.FG >>
		m_BulletConfig.FB >> m_BulletConfig.OR >> m_BulletConfig.OG >>
		m_BulletConfig.OB >> m_BulletConfig.OT >> m_BulletConfig.V >>
		m_BulletConfig.L;
	std::cout << m_BulletConfig.SR << std::endl;
	std::cout << m_BulletConfig.CR << std::endl;
	std::cout << m_BulletConfig.S << std::endl;
	std::cout << m_BulletConfig.FR << std::endl;
	std::cout << m_BulletConfig.FG << std::endl;
	std::cout << m_BulletConfig.FB << std::endl;
	std::cout << m_BulletConfig.OR << std::endl;
	std::cout << m_BulletConfig.OG << std::endl;
	std::cout << m_BulletConfig.OB << std::endl;
	std::cout << m_BulletConfig.OT << std::endl;
	std::cout << m_BulletConfig.V << std::endl;
	std::cout << m_BulletConfig.L;
	std::cout << "\n";
	spawnPlayer();
}

void Game::reset(void) {
	EntityVec entities = m_entities.getEntities();
	for (auto &e : entities) {
		e->destroy();
	}
	spawnPlayer();
	m_score = 0;
	m_currentFrame = 0;
}

// NOTE: Private:

void Game::sMovement(void) {
	// FIXME: Move to handle player movement
	m_player->cTransform->velocity = {0, 0};
	if (m_player->cInput->up)
		m_player->cTransform->velocity.y -= m_playerConfig.S;
	if (m_player->cInput->down)
		m_player->cTransform->velocity.y += m_playerConfig.S;
	if (m_player->cInput->left)
		m_player->cTransform->velocity.x -= m_playerConfig.S;
	if (m_player->cInput->right)
		m_player->cTransform->velocity.x += m_playerConfig.S;
	for (auto &e : m_entities.getEntities()) {
		if (e->cTransform) {
			e->cTransform->prevPos = e->cTransform->pos;
			e->cTransform->pos += e->cTransform->velocity;
		}
	}
}

void Game::sUserInput(void) {
	// FIXME: Handle user input
	while (const std::optional event = m_window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			m_running = false;
		}
		if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->code) {
				case sf::Keyboard::Key::Escape:
					m_running = false;
					break;
				case sf::Keyboard::Key::W:
				case sf::Keyboard::Key::Up:
					m_player->cInput->up = true;
					break;
				case sf::Keyboard::Key::A:
				case sf::Keyboard::Key::Left:
					m_player->cInput->left = true;
					break;
				case sf::Keyboard::Key::S:
				case sf::Keyboard::Key::Down:
					m_player->cInput->down = true;
					break;
				case sf::Keyboard::Key::D:
				case sf::Keyboard::Key::Right:
					m_player->cInput->right = true;
					break;
				case sf::Keyboard::Key::R:
					if (!m_paused) {
						reset();
					}
					break;
				case sf::Keyboard::Key::P:
					m_paused = !m_paused;
					break;
				default:
					break;
			}
		}
		if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			switch (keyReleased->code) {
				case sf::Keyboard::Key::W:
				case sf::Keyboard::Key::Up:
					m_player->cInput->up = false;
					break;
				case sf::Keyboard::Key::A:
				case sf::Keyboard::Key::Left:
					m_player->cInput->left = false;
					break;
				case sf::Keyboard::Key::S:
				case sf::Keyboard::Key::Down:
					m_player->cInput->down = false;
					break;
				case sf::Keyboard::Key::D:
				case sf::Keyboard::Key::Right:
					m_player->cInput->right = false;
					break;
				default:
					break;
			}
		}
		if (const auto *mouseButton =
				event->getIf<sf::Event::MouseButtonPressed>()) {
			Vec2 mousePos(sf::Mouse::getPosition(m_window).x,
						  sf::Mouse::getPosition(m_window).y);
			if (mouseButton->button == sf::Mouse::Button::Left) {
				spawnBullet(m_player, mousePos);
			}
			if (mouseButton->button == sf::Mouse::Button::Right) {
				spawnSpecialWeapon(m_player);
			}
		}
	}
}

void Game::sLifeSpan(void) {
	// FIXME: Add logic
}

void Game::sRender(void) {
	m_window.clear();

	for (auto &e : m_entities.getEntities()) {
		e->cShape->circle.setPosition(
			sf::Vector2f(e->cTransform->pos.x, e->cTransform->pos.y));
		e->cTransform->angle += 1.0f;
		sf::Angle angle = sf::degrees(e->cTransform->angle);
		e->cShape->circle.setRotation(angle);
		m_window.draw(e->cShape->circle);
	}
	m_window.display();
}

void Game::sEnemySpawner(void) {
	// FIXME: use m_currentFrame - m_lastEnemySpawnTime
	if (m_currentFrame % m_enemyConfig.SP == 0)
		spawnEnemy();
}

bool Game::entitiesCollide(const EntityPtr &a, const EntityPtr &b) {
	if (!a->isActive() || !b->isActive()) {
		return (false);
	}
	float dist = a->cTransform->pos.dist(b->cTransform->pos);
	float aR2 = a->cCollision->radius * a->cCollision->radius;
	float bR2 = b->cCollision->radius * b->cCollision->radius;
	return (dist * dist <= aR2 + bR2);
}

void Game::sCollision(void) {
	for (auto &e : m_entities.getEntities("enemy")) {
		for (auto &b : m_entities.getEntities("bullet")) {
			if (entitiesCollide(b, e)) {
				b->destroy();
				e->destroy();
				spawnSmallEnemies(e);
			}
		}
		if (e->isActive()) {
			if (entitiesCollide(e, m_player)) {
				m_player->destroy();
			} else {
				bounceObjectFromWalls(e);
			}
		}
	}
	bounceObjectFromWalls(m_player);
}

void Game::spawnPlayer(void) {
	auto  player = m_entities.addEntity("player");
	float middleX = m_window.getSize().x / 2.0f;
	float middleY = m_window.getSize().y / 2.0f;
	player->cTransform =
		new CTransform(Vec2(middleX, middleY), Vec2(1.0f, 1.0f), 0.0f);
	player->cShape = new CShape(
		m_playerConfig.SR, m_playerConfig.V,
		sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
		m_playerConfig.OT);
	player->cCollision = new CCollision(m_playerConfig.CR);
	player->cInput = new CInput();

	m_player = player;
}

void Game::spawnEnemy(void) {
	auto enemy = m_entities.addEntity("enemy");

	Vec2 randomPos =
		randomVec2InsideWindowBasedOnCollisionRadius(m_enemyConfig.CR);
	while (m_player->cTransform->pos.dist(randomPos) < m_playerConfig.CR * 2) {
		randomPos =
			randomVec2InsideWindowBasedOnCollisionRadius(m_enemyConfig.CR);
	}

	Vec2 randomVelocity(
		randomFloatWithinRange(-static_cast<int>(m_window.getSize().x),
							   static_cast<int>(m_window.getSize().x)),
		randomFloatWithinRange(-static_cast<int>(m_window.getSize().y),
							   static_cast<int>(m_window.getSize().y)));
	randomVelocity.normalize();
	randomVelocity *=
		randomFloatWithinRange(m_enemyConfig.SMIN, m_enemyConfig.SMAX);

	enemy->cTransform = new CTransform(randomPos, randomVelocity, 0.0f);

	// randomize vertices based on VMIN and VMAX
	std::uniform_int_distribution<std::mt19937::result_type>
		randomVerticesCount(m_enemyConfig.VMIN, m_enemyConfig.VMAX);
	int vertices = randomVerticesCount(m_randomDevice);

	enemy->cShape = new CShape(
		m_enemyConfig.SR, vertices, sf::Color(0, 0, 0),
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
		m_enemyConfig.OT);
	enemy->cCollision = new CCollision(m_enemyConfig.CR);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> &entity) {
	std::cout << "Spawn small enemies" << std::endl;
	(void)entity;
}

void Game::spawnBullet(std::shared_ptr<Entity> &entity, const Vec2 &mousePos) {
	auto bullet = m_entities.addEntity("bullet");
	bullet->cTransform = new CTransform(mousePos, Vec2(0, 0), 0);
	bullet->cShape =
		new CShape(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2);
	bullet->cCollision = new CCollision(10);
	(void)entity;
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> &entity) {
	std::cout << "SPECIAL\n";
	(void)entity;
}

float Game::randomFloatWithinRange(float min, float max) {
	return (std::uniform_real_distribution<float>{min, max}(m_engine));
}

Vec2 Game::randomVec2InsideWindowBasedOnCollisionRadius(const float radius) {
	int r = std::ceil(radius);
	std::uniform_int_distribution<std::mt19937::result_type> distWidth(
		r, m_windowConfig.size.x - r);
	std::uniform_int_distribution<std::mt19937::result_type> distHeight(
		r, m_windowConfig.size.y - r);
	return (Vec2(distWidth(m_randomDevice), distHeight(m_randomDevice)));
}

void Game::reflectObjectVelocity(EntityPtr e, Vec2 surfaceNormal) {
	surfaceNormal.normalize();
	float dotProduct = dot(e->cTransform->velocity, surfaceNormal);
	e->cTransform->velocity -= 2 * (dotProduct)*surfaceNormal;
}

void Game::bounceObjectFromWalls(EntityPtr e) {
	unsigned int screenWidth = m_windowConfig.size.x;
	unsigned int screenHeight = m_windowConfig.size.y;

	float xSize = e->cShape->circle.getLocalBounds().size.x / 2.0f;
	float ySize = e->cShape->circle.getLocalBounds().size.y / 2.0f;
	if (e->cTransform->pos.x - xSize <= 0) {
		e->cTransform->pos.x = e->cTransform->prevPos.x;
		reflectObjectVelocity(e, Vec2(1, 0));
	}
	if (e->cTransform->pos.y - ySize <= 0) {
		e->cTransform->pos.y = e->cTransform->prevPos.y;
		reflectObjectVelocity(e, Vec2(0, 1));
	}
	if (e->cTransform->pos.x + xSize >= screenWidth) {
		e->cTransform->pos.x = e->cTransform->prevPos.x;
		reflectObjectVelocity(e, Vec2(-1, 0));
	}
	if (e->cTransform->pos.y + ySize >= screenHeight) {
		e->cTransform->pos.y = e->cTransform->prevPos.y;
		reflectObjectVelocity(e, Vec2(0, -1));
	}
}
