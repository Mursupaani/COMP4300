#include "Entity.hpp"

Entity::Entity(const std::string &tag, const size_t id)
	: m_id(id), m_tag(tag) {}

Entity::~Entity(void) {
	if (cTransform)
		delete cTransform;
	if (cName)
		delete cName;
	if (cShape)
		delete cShape;
	if (cBBox)
		delete cBBox;
}

std::string Entity::tag(void) const {
	return (m_tag);
}

bool Entity::isAlive(void) const {
	return (m_alive);
}

size_t Entity::id(void) const {
	return (m_id);
}

void Entity::destroy(void) {
	m_alive = false;
}

std::ostream &operator<<(std::ostream &stream, const Entity &clock) {
	(void)clock;
	return (stream);
}
