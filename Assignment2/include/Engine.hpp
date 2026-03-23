#pragma once
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "Components.hpp"
#include "EntityManager.hpp"

class Engine {
	private:
		const std::string m_homeDir = std::getenv("HOME");
		sf::Font		  m_font;
		unsigned int	  m_fontSize;
		size_t			  m_currentFrame = 0;
		EntityManager	  m_entityManager;

		void bounceObjectsFromWalls(void);
		void parseConfig(const std::string &configFilePath);

		// NOTE: Systems:
		void sUserInput(void);
		void sMovement(void);
		void sRender(void);
		void sPhysics(void);
		void sCollision(void);

	public:
		sf::RenderWindow window;
		sf::Vector2u	 windowSize;

		Engine(void) = delete;
		Engine(const std::string &configFilePath);

		void mainLoop(void);
};
