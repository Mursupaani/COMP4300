#include "Entity.hpp"

Entity::Entity(void) {}

Entity::Entity(const Entity &other) {
	(void)other;
}

Entity &Entity::operator=(const Entity &other) {
	if (this == &other)
		return (*this);
	return (*this);
}
Entity::~Entity(void) {}

std::ostream &operator<<(std::ostream &stream, const Entity &clock) {
	(void)clock;
	return (stream);
}
