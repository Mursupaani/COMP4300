#include "Game.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <fstream>

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

// NOTE: Private:

void Game::sMovement(void) {
	for (auto &e : m_entities.getEntities()) {
		if (e->cTransform)
			e->cTransform->pos += e->cTransform->velocity;
	}
}

void Game::sUserInput(void) {
	// FIXME: Handle user input
}

void Game::sLifeSpan(void) {
	// FIXME: Add logic
}

void Game::sRender(void) {
	m_window.clear();

	for (auto &e : m_entities.getEntities()) {
		// if (e->cTransform && e->cShape) {}
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
	// FIXME: Add logic
}

void Game::sCollision(void) {
	// FIXME: Add logic
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
	float ex = m_window.getSize().x / 2.0f;
	float ey = m_window.getSize().y / 2.0f;
	enemy->cTransform = new CTransform(Vec2(ex, ey), Vec2(1.0f, 1.0f), 0.0f);
	enemy->cShape =
		new CShape(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
	enemy->cInput = new CInput();

	m_player = enemy;
	m_lastEnemySpawnTime = m_currentFrame;
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
