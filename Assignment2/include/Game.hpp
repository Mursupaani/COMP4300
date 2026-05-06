#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <fstream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include "EntityManager.hpp"
#include "Vec2.hpp"

struct PlayerConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
		float S;
};
struct EnemyConfig {
		int	  SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SP;
		float SMIN, SMAX;
};
struct BulletConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
		float S;
};
struct WindowConfig {
		sf::Vector2u size{0, 0};
		unsigned int framelimit = 60;
		bool		 fullscreen = 0;
};
struct FontConfig {
		std::string	 path{};
		unsigned int size = 12;
		uint32_t	 colorR;
		uint32_t	 colorG;
		uint32_t	 colorB;
};

class Game {
	private:
		sf::RenderWindow m_window{};
		sf::State		 m_windowState = sf::State::Windowed;
		WindowConfig	 m_windowConfig{};
		sf::Font		 m_font{};
		sf::Color		 m_fontColor{};
		FontConfig		 m_fontConfig{};
		sf::Text		*m_scoreText = nullptr;
		sf::Text		*m_specialText = nullptr;
		EntityManager	 m_entities{};
		PlayerConfig	 m_playerConfig{};
		EnemyConfig		 m_enemyConfig{};
		BulletConfig	 m_BulletConfig{};
		int				 m_score = 0;
		bool			 m_paused = false;
		bool			 m_running = true;

		size_t m_currentFrame = 0;
		size_t m_lastEnemySpawnTime = 0;
		size_t m_lastShoot = 0;
		size_t m_shootCooldown = 0;
		bool   m_shootAvailable = true;
		size_t m_lastSpecialUse = 0;
		size_t m_specialCooldown = 0;
		bool   m_specialAvailable = true;

		std::random_device m_randomDevice{};
		std::mt19937	   m_engine{m_randomDevice()};

		std::shared_ptr<Entity> m_player;

		void init(const std::string &path);

		// NOTE: Systems:
		void sMovement(void);
		void sUserInput(void);
		void sLifeSpan(void);
		void sRender(void);
		void sEnemySpawner(void);

		void sCollision(void);
		bool entitiesCollide(const EntityPtr &a, const EntityPtr &b);

		void spawnPlayer(void);
		void spawnEnemy(void);
		void spawnSmallEnemies(std::shared_ptr<Entity> &entity);
		void spawnBullet(std::shared_ptr<Entity> &entity, Vec2 &direction);
		void spawnSpecialWeapon(std::shared_ptr<Entity> &entity,
								const Vec2				&mousePos);

		void reset(void);

		void bounceObjectFromWalls(EntityPtr e);

		void  parseConfig(const std::string &config);
		Vec2  randomVec2InsideWindowBasedOnCollisionRadius(const float radius);
		float randomFloatWithinRange(float min, float max);

		void reflectObjectVelocity(EntityPtr e, Vec2 surfaceNormal);

	public:
		Game(const std::string &config);
		~Game(void);

		void run(void);
};
