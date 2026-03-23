#include "Engine.hpp"

#include "EntityManager.hpp"

// NOTE: Public:
Engine::Engine(const std::string &configFilePath) {
	parseConfig(configFilePath);
}

void Engine::mainLoop(void) {
	m_entityManager.update();
	sUserInput();
	sMovement();
	sCollision();
	sRender();
	++m_currentFrame;
}

// NOTE: Private:
void Engine::sUserInput(void) {
	// FIXME: Handle user input
}

void Engine::sMovement(void) {
	for (auto &e : m_entityManager.getEntities()) {
		if (e->cTransform)
			e->cTransform->pos += e->cTransform->velocity;
	}
}

void Engine::sRender(void) {
	for (auto &e : m_entityManager.getEntities()) {
		if (e->cTransform && e->cShape) {
			e->cShape->shape.setPosition(
				sf::Vector2f(e->cTransform->pos.x, e->cTransform->pos.y));
			window.draw(e->cShape->shape);
		}
	}
}

void Engine::sPhysics(void) {
	for (auto &e : m_entityManager.getEntities()) {
		if (e->cBBox)
			(void)e;
	}
}

void Engine::sCollision(void) {}

void Engine::bounceObjectsFromWalls(void) {
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

void Engine::parseConfig(const std::string &configFilePath) {
	std::ifstream configFile(configFilePath);
	std::string	  token;
	if (!configFile)
		throw std::runtime_error("Couldn't open config file");
	{
		configFile >> token;
		if (token == "Window") {
			unsigned int windowWidth;
			unsigned int windowHeight;
			configFile >> windowWidth >> windowHeight;
			windowSize = sf::Vector2u(windowWidth, windowHeight);
		} else
			throw std::runtime_error("Missing window configurations");
	}
	{
		configFile >> token;
		if (token == "Font") {
			std::string	 fontPath;
			unsigned int fontSize;
			unsigned int red;
			unsigned int green;
			unsigned int blue;
			configFile >> fontPath >> fontSize >> red >> green >> blue;
			if (!m_font.openFromFile(fontPath)) {
				throw std::runtime_error("Couldn't open font");
			}
			m_fontSize = fontSize;
		} else
			throw std::runtime_error("Missing font configurations");
	}
	while (configFile >> token) {
		if (token == "Circle" || token == "Rectangle") {
			// Object::ShapeType type;
			std::string	 shapeName;
			unsigned int width;
			unsigned int height;
			float		 xSpeed;
			float		 ySpeed;
			unsigned int red;
			unsigned int green;
			unsigned int blue;
			unsigned int extra;
			// if (token == "Circle")
			// type = Object::ShapeType::CIRCLE;
			// else
			// type = Object::ShapeType::RECTANGLE;
			if (!(configFile >> shapeName >> width >> height >> xSpeed >>
				  ySpeed >> red >> green >> blue >> extra)) {
				throw std::runtime_error(
					"Malformed " + token +
					" config: missing or invalid attributes for " + shapeName);
			}
			// configFile >> shapeName >> width >> height >> xSpeed >> ySpeed >>
			// 	red >> green >> blue >> extra;
			// _objects.emplace_back(Object(
			// 	type, sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f),
			// 	_font, _fontSize, shapeName, width, height, xSpeed, ySpeed, red,
			// 	green, blue));
		} else
			throw std::runtime_error("Unexpected token " + token);
	}
	// if (windowSize.x > 0 && windowSize.y > 0 && _objects.size() > 0) {
	// 	window = sf::RenderWindow(sf::VideoMode(windowSize), "SFML");
	// 	window.setFramerateLimit(60);
	// } else {
	// 	throw std::runtime_error("Invalid config file");
	// }
}
