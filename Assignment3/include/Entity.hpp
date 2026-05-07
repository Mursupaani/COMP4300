#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

#include "Components.hpp"
#include "EntityManager.hpp"

class Entity {
		friend class EntityManager;

	private:
		bool		 m_active = true;
		const size_t m_id = 0;
		std::string	 m_tag = "Default";

		Entity(const std::string &tag, const size_t id);

	public:
		// WARN: If problems, change to shared_ptr
		CTransform *cTransform = nullptr;
		CShape	   *cShape = nullptr;
		CCollision *cCollision = nullptr;
		CInput	   *cInput = nullptr;
		CScore	   *cScore = nullptr;
		CLifespan  *cLifespan = nullptr;

		Entity(void) = delete;
		Entity(const Entity &other) = delete;
		Entity &operator=(const Entity &other) = delete;
		~Entity(void);

		bool		 isActive(void) const;
		std::string &tag(void);
		size_t		 id(void) const;
		void		 destroy(void);
};

std::ostream &operator<<(std::ostream &stream, const Entity &vec);
