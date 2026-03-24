#include "Entity.hpp"

Entity::Entity(const std::string &tag, const size_t id) : m_id(id), m_tag(tag) {
	// this->cShape = new CShape();
	// this->cShape->shape = sf::CircleShape(10, 4);
	// this->cShape->shape.setOrigin(sf::Vector2f(
	// 	this->cShape->shape.getRadius(), this->cShape->shape.getRadius()));
}

Entity::~Entity(void) {
	if (cTransform)
		delete cTransform;
	if (cShape)
		delete cShape;
	if (cCollision)
		delete cCollision;
	if (cInput)
		delete cInput;
	if (cScore)
		delete cScore;
	if (cLifespan)
		delete cLifespan;
}

std::string &Entity::tag(void) {
	return (m_tag);
}

bool Entity::isActive(void) const {
	return (m_active);
}

size_t Entity::id(void) const {
	return (m_id);
}

void Entity::destroy(void) {
	m_active = false;
}

std::ostream &operator<<(std::ostream &stream, const Entity &clock) {
	(void)clock;
	return (stream);
}
