#include <Object.hpp>

Object::Object(const Object::ShapeType shape, const sf::Vector2f &origin,
			   const sf::Font &font, unsigned int fontSize,
			   const std::string &name, const unsigned int width,
			   const unsigned int height, const float xSpeed,
			   const float ySpeed, const unsigned int red,
			   const unsigned int green, const unsigned int blue)
	: _name(sf::Text(font, name, fontSize)),
	  _width(width),
	  _height(height),
	  _xSpeed(xSpeed),
	  _ySpeed(ySpeed),
	  _color(red, green, blue) {
	switch (shape) {
		case Object::ShapeType::CIRCLE: {
			_shape = std::make_unique<sf::CircleShape>(_width, _height);
		} break;
		case Object::ShapeType::RECTANGLE: {
			_shape = std::make_unique<sf::RectangleShape>(
				sf::Vector2f(_width, _height));
		} break;
		default:
			throw std::runtime_error("Invalid shape type");
	}
	_shape->setFillColor(_color);
	_shape->setPosition(origin);
	_name.setFillColor(sf::Color::White);
	sf::FloatRect shapeBounds = _shape->getLocalBounds();
	_shape->setOrigin(
		sf::Vector2f(shapeBounds.position.x + shapeBounds.size.x / 2.0f,
					 shapeBounds.position.y + shapeBounds.size.y / 2));
	sf::FloatRect textBounds = _name.getLocalBounds();
	_name.setOrigin(
		sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f,
					 textBounds.position.y + textBounds.size.y / 2));
	_name.setPosition(_shape->getPosition());
}

Object::Object(const Object::ShapeType shape, const sf::Font &font,
			   const std::string &text)
	: _name(font, text) {
	switch (shape) {
		case Object::ShapeType::CIRCLE: {
			_shape = std::make_unique<sf::CircleShape>(25);
			_shape->setFillColor(sf::Color::Red);
			_shape->setPosition(sf::Vector2f(25, 25));
			_name.setFillColor(sf::Color::Black);
		} break;
		case Object::ShapeType::RECTANGLE: {
			_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 50));
			_shape->setFillColor(sf::Color::Green);
			_shape->setPosition(sf::Vector2f(700, 360));
			_name.setFillColor(sf::Color::White);
		} break;
		default:
			throw std::runtime_error("Invalid shape type");
	}
	sf::FloatRect shapeBounds = _shape->getLocalBounds();
	_shape->setOrigin(
		sf::Vector2f(shapeBounds.position.x + shapeBounds.size.x / 2.0f,
					 shapeBounds.position.y + shapeBounds.size.y / 2));
	sf::FloatRect textBounds = _name.getLocalBounds();
	_name.setOrigin(
		sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f,
					 textBounds.position.y + textBounds.size.y / 2));
	_name.setPosition(_shape->getPosition());
}

const sf::Vector2f Object::getPosition(void) {
	return (_shape->getPosition());
}

void Object::setPosition(const sf::Vector2f &pos) {
	_shape->setPosition(pos);
	_name.setPosition(_shape->getPosition());
}
sf::Shape &Object::getShape(void) {
	return (*_shape);
}

sf::Text &Object::getText(void) {
	return _name;
}

void Object::setVSpeed(int speed) {
	_ySpeed = speed;
}

void Object::setHSpeed(int speed) {
	_xSpeed = speed;
}

float Object::getHSpeed(void) const {
	return _xSpeed;
}

float Object::getVSpeed(void) const {
	return _ySpeed;
}

Object::~Object(void) {}
