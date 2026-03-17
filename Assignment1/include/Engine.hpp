#pragma once
#include <SFML/Graphics.hpp>
#include <exception>
#include <fstream>
#include <stdexcept>

#include "Object.hpp"

class Engine {
	private:
		std::vector<Object> _objects;
		const std::string	_homeDir = std::getenv("HOME");
		sf::Font			_font;
		unsigned int		_fontSize;

		void bounceObjectsFromWalls(void);
		void moveObjects(void);
		void parseConfig(const std::string &configFilePath);

	public:
		Engine(void) = delete;
		Engine(const std::string &configFilePath);
		void drawObjects(void);

		sf::RenderWindow window;
		sf::Vector2u	 windowSize;
};
