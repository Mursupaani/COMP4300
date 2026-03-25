#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstddef>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "EntityManager.hpp"
#include "Vec2.hpp"

struct PlayerConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
		float S;
};
struct EnemyConfig {
		int	  SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
		float SMIN, SMAX;
};
struct BulletConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
		float S;
};

class Game {
	private:
		sf::RenderWindow m_window;
		unsigned int	 m_framerateLimit = 60;
		sf::State		 m_windowState = sf::State::Windowed;
		EntityManager	 m_entities;
		sf::Font		 m_font;
		sf::Text		*m_text = nullptr;
		PlayerConfig	 m_playerConfig;
		EnemyConfig		 m_enemyConfig;
		BulletConfig	 m_BulletConfig;
		int				 m_score = 0;
		size_t			 m_currentFrame = 0;
		size_t			 m_lastEnemySpawnTime = 0;
		bool			 m_paused = false;
		bool			 m_running = true;

		std::shared_ptr<Entity> m_player;

		void init(const std::string &path);
		void setPaused(const bool paused);

		// NOTE: Systems:
		void sMovement(void);
		void sUserInput(void);
		void sLifeSpan(void);
		void sRender(void);
		void sEnemySpawner(void);
		void sCollision(void);

		void spawnPlayer(void);
		void spawnEnemy(void);
		void spawnSmallEnemies(std::shared_ptr<Entity> &entity);
		void spawnBullet(std::shared_ptr<Entity> &entity, const Vec2 &mousePos);
		void spawnSpecialWeapon(std::shared_ptr<Entity> &entity);

		void reset(void);

		// const std::string m_homeDir = std::getenv("HOME");
		unsigned int m_fontSize = 12;
		sf::Vector2u windowSize{1920, 1080};

		void bounceObjectsFromWalls(void);
		void parseConfig(const std::string &config);

	public:
		Game(const std::string &config);
		~Game(void);

		void run(void);
};
