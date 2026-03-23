#include "EntityManager.hpp"

EntityManager::EntityManager(void) {}

EntityManager::EntityManager(const EntityManager &other) {
	(void)other;
}

EntityManager &EntityManager::operator=(const EntityManager &other) {
	if (this == &other)
		return (*this);
	return (*this);
}
EntityManager::~EntityManager(void) {}

std::ostream &operator<<(std::ostream &stream, const EntityManager &clock) {
	(void)clock;
	return (stream);
}
