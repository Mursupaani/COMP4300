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
#include <cstdlib>
#include <fstream>
#include <memory>

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
		m_entities.update();

		if (!m_paused) {
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		}
		sRender();

		// NOTE: increment the current frame
		//  may need to be moved when pause implemented
		++m_currentFrame;
	}
	m_window.close();
}

void Game::init(const std::string &path) {
	// TODO: Read in config file here. Use the premade xConfig variables
	// 	window = sf::RenderWindow(sf::VideoMode(windowSize), "SFML");
	std::ifstream fin(path);

	// Do this for all structs
	fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >>
		m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >>
		m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >>
		m_playerConfig.OT >> m_playerConfig.V;

	// Set up window parameters
	m_window.create(sf::VideoMode(windowSize), "Geometry Wars",
					sf::Style::Default, m_windowState);
	m_window.setFramerateLimit(m_framerateLimit);

	spawnPlayer();
}

void Game::reset(void) {
	EntityVec &enemies = m_entities.getEntities("enemy");
	for (auto &e : enemies)
		e->destroy();
	m_player->destroy();
	spawnPlayer();
	m_score = 0;
}

// NOTE: Private:

void Game::sMovement(void) {
	// FIXME: Move to handle player movement
	m_player->cTransform->velocity = {0, 0};
	if (m_player->cInput->up)
		m_player->cTransform->velocity.y = -5;
	if (m_player->cInput->down)
		m_player->cTransform->velocity.y = 5;
	if (m_player->cInput->left)
		m_player->cTransform->velocity.x = -5;
	if (m_player->cInput->right)
		m_player->cTransform->velocity.x = 5;
	for (auto &e : m_entities.getEntities()) {
		if (e->cTransform)
			e->cTransform->pos += e->cTransform->velocity;
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
					m_player->cInput->up = true;
					break;
				case sf::Keyboard::Key::A:
					m_player->cInput->left = true;
					break;
				case sf::Keyboard::Key::S:
					m_player->cInput->down = true;
					break;
				case sf::Keyboard::Key::D:
					m_player->cInput->right = true;
					break;
				case sf::Keyboard::Key::R:
					reset();
					break;
				default:
					break;
			}
		}
		if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			switch (keyReleased->code) {
				case sf::Keyboard::Key::W:
					m_player->cInput->up = false;
					break;
				case sf::Keyboard::Key::A:
					m_player->cInput->left = false;
					break;
				case sf::Keyboard::Key::S:
					m_player->cInput->down = false;
					break;
				case sf::Keyboard::Key::D:
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
	// FIXME: use m_currendFrame - m_lastEnemySpawnTime
	if (m_currentFrame % 60 == 0)
		spawnEnemy();
}

void Game::sCollision(void) {
	for (auto &b : m_entities.getEntities("bullet")) {
		for (auto &e : m_entities.getEntities("enemy")) {
			// FIXME: Add logic
			(void)b;
			(void)e;
		}
	}
}

void Game::spawnPlayer(void) {
	auto  player = m_entities.addEntity("player");
	float middleX = m_window.getSize().x / 2.0f;
	float middleY = m_window.getSize().y / 2.0f;
	player->cTransform =
		new CTransform(Vec2(middleX, middleY), Vec2(1.0f, 1.0f), 0.0f);
	player->cShape =
		new CShape(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
	player->cInput = new CInput();

	m_player = player;
}

void Game::spawnEnemy(void) {
	// Make sure enemy is spawned according to m_enemyConfig
	// Must be completely within window
	auto enemy = m_entities.addEntity("enemy");

	// randomize position
	float ex = std::rand() % m_window.getSize().x;
	float ey = std::rand() % m_window.getSize().y;

	// randomize velocity vector (direction) based on speed
	float rdx = 1.0f;
	float rdy = 1.0f;

	enemy->cTransform = new CTransform(Vec2(ex, ey), Vec2(rdx, rdy), 0.0f);

	// randomize vertices based on VMIN and VMAX
	int vertices = 4;

	m_enemyConfig.SR = 32.0f;
	m_enemyConfig.OR = 255;
	m_enemyConfig.OG = 0;
	m_enemyConfig.OB = 0;
	m_enemyConfig.OT = 0;
	enemy->cShape = new CShape(
		m_enemyConfig.SR, vertices,
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
		m_enemyConfig.OT);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> &entity) {
	(void)entity;
}

void Game::spawnBullet(std::shared_ptr<Entity> &entity, const Vec2 &mousePos) {
	auto bullet = m_entities.addEntity("bullet");
	bullet->cTransform = new CTransform(mousePos, Vec2(0, 0), 0);
	bullet->cShape =
		new CShape(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2);
	(void)entity;
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> &entity) {
	std::cout << "SPECIAL\n";
	(void)entity;
}

void Game::bounceObjectsFromWalls(void) {
	// unsigned int screenWidth = windowSize.x;
	// unsigned int screenHeight = windowSize.y;

	// for (auto &object : _objects) {
	// 	float xSize = object.getShape().getLocalBounds().size.x / 2.0f;
	// 	float ySize = object.getShape().getLocalBounds().size.y / 2.0f;
	// 	if (object.getPosition().x - xSize <= 0)
	// 		object.setHSpeed(object.getHSpeed() * -1);
	// 	if (object.getPosition().y - ySize <= 0)
	// 		object.setVSpeed(object.getVSpeed() * -1);
	// 	if (object.getPosition().x + xSize >= screenWidth)
	// 		object.setHSpeed(object.getHSpeed() * -1);
	// 	if (object.getPosition().y + ySize >= screenHeight)
	// 		object.setVSpeed(object.getVSpeed() * -1);
	// }
}

// void Game::init(const std::string &configFilePath) {
// 	std::ifstream configFile(configFilePath);
// 	std::string	  token;
// 	if (!configFile)
// 		throw std::runtime_error("Couldn't open config file");
// 	{
// 		configFile >> token;
// 		if (token == "Window") {
// 			unsigned int windowWidth;
// 			unsigned int windowHeight;
// 			configFile >> windowWidth >> windowHeight;
// 			windowSize = sf::Vector2u(windowWidth, windowHeight);
// 		} else
// 			throw std::runtime_error("Missing window configurations");
// 	}
// 	{
// 		configFile >> token;
// 		if (token == "Font") {
// 			std::string	 fontPath;
// 			unsigned int fontSize;
// 			unsigned int red;
// 			unsigned int green;
// 			unsigned int blue;
// 			configFile >> fontPath >> fontSize >> red >> green >> blue;
// 			if (!m_font.openFromFile(fontPath)) {
// 				throw std::runtime_error("Couldn't open font");
// 			}
// 			m_fontSize = fontSize;
// 		} else
// 			throw std::runtime_error("Missing font configurations");
// 	}
// 	while (configFile >> token) {
// 		if (token == "Circle" || token == "Rectangle") {
// 			// Object::ShapeType type;
// 			std::string	 shapeName;
// 			unsigned int width;
// 			unsigned int height;
// 			float		 xSpeed;
// 			float		 ySpeed;
// 			unsigned int red;
// 			unsigned int green;
// 			unsigned int blue;
// 			unsigned int extra;
// 			// if (token == "Circle")
// 			// type = Object::ShapeType::CIRCLE;
// 			// else
// 			// type = Object::ShapeType::RECTANGLE;
// 			if (!(configFile >> shapeName >> width >> height >> xSpeed >>
// 				  ySpeed >> red >> green >> blue >> extra)) {
// 				throw std::runtime_error(
// 					"Malformed " + token +
// 					" config: missing or invalid attributes for " + shapeName);
// 			}
// 			// configFile >> shapeName >> width >> height >> xSpeed >> ySpeed >>
// 			// 	red >> green >> blue >> extra;
// 			// _objects.emplace_back(Object(
// 			// 	type, sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f),
// 			// 	_font, _fontSize, shapeName, width, height, xSpeed, ySpeed, red,
// 			// 	green, blue));
// 		} else
// 			throw std::runtime_error("Unexpected token " + token);
// 	}
// 	// if (windowSize.x > 0 && windowSize.y > 0 && _objects.size() > 0) {
// 	// 	window = sf::RenderWindow(sf::VideoMode(windowSize), "SFML");
// 	// 	window.setFramerateLimit(60);
// 	// } else {
// 	// 	throw std::runtime_error("Invalid config file");
// 	// }
// }
