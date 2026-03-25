#pragma once
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "Entity.hpp"

class Entity;

using EntityPtr = typename std::shared_ptr<Entity>;
using EntityVec = typename std::vector<EntityPtr>;
using EntityMap = typename std::unordered_map<std::string, EntityVec>;

class EntityManager {
	private:
		EntityVec m_entities;
		EntityVec m_entitiesToAdd;
		EntityMap m_entityMap;
		size_t	  m_totalEntities = 0;

	public:
		EntityManager(void);
		EntityManager(const EntityManager &other) = delete;
		EntityManager &operator=(const EntityManager &other) = delete;
		~EntityManager(void);

		void update(void);

		EntityPtr  addEntity(const std::string &tag);
		EntityVec &getEntities();
		EntityVec &getEntities(const std::string &tag);
		void	   removeDeadEntities(EntityVec &entities);
};

std::ostream &operator<<(std::ostream &stream, const EntityManager &vec);
