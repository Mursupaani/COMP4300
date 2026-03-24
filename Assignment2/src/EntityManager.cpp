#include "EntityManager.hpp"

#include <memory>

#include "Entity.hpp"

EntityManager::EntityManager(void) {}

EntityManager::~EntityManager(void) {}

void EntityManager::update(void) {
	for (auto &e : m_toAdd) {
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	auto ne = remove_if(m_entities.begin(), m_entities.end(),
						[](EntityPtr &e) { return (e->isActive() == false); });
	m_entities.erase(ne, m_entities.end());

	for (auto &[tag, vec] : m_entityMap) {
		auto neMap = remove_if(vec.begin(), vec.end(), [](EntityPtr &e) {
			return (e->isActive() == false);
		});
		vec.erase(neMap, vec.end());
	}

	m_toAdd.clear();
}

EntityPtr EntityManager::addEntity(const std::string &tag) {
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_toAdd.push_back(e);
	return (e);
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
