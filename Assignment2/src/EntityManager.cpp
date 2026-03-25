#include "EntityManager.hpp"

#include <memory>

#include "Entity.hpp"

EntityManager::EntityManager(void) {}

EntityManager::~EntityManager(void) {}

void EntityManager::update(void) {
	for (auto &e : m_entitiesToAdd) {
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_entitiesToAdd.clear();

	removeDeadEntities(m_entities);
	for (auto &[type, entityVec] : m_entityMap) {
		removeDeadEntities(entityVec);
	}
}

void EntityManager::removeDeadEntities(EntityVec &entities) {
	auto ne = remove_if(entities.begin(), entities.end(),
						[](EntityPtr &e) { return (e->isActive() == false); });
	entities.erase(ne, entities.end());
}

EntityPtr EntityManager::addEntity(const std::string &tag) {
	auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_entitiesToAdd.push_back(entity);
	return (entity);
}
EntityVec &EntityManager::getEntities(void) {
	return (m_entities);
}
EntityVec &EntityManager::getEntities(const std::string &tag) {
	return (m_entityMap[tag]);
}
std::ostream &operator<<(std::ostream &stream, const EntityManager &clock) {
	(void)clock;
	return (stream);
}
