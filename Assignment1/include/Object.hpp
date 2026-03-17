#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class Object {
	private:
		std::unique_ptr<sf::Shape> _shape;
		sf::Text				   _name;
		unsigned int			   _width;
		unsigned int			   _height;
		float					   _xSpeed;
		float					   _ySpeed;
		sf::Color				   _color;

	public:
		enum class ShapeType { CIRCLE, RECTANGLE };

		Object(void) = delete;
		Object(const Object::ShapeType shape, const sf::Vector2f &origin,
			   const sf::Font &font, unsigned int fontSize,
			   const std::string &name, const unsigned int width,
			   const unsigned int height, const float xSpeed,
			   const float ySpeed, const unsigned int red,
			   const unsigned int green, const unsigned int blue);
		Object(const Object::ShapeType shape, const sf::Font &font,
			   const std::string &name);
		Object(Object &&other) noexcept = default;
		~Object(void);

		void			   setHSpeed(int speed);
		void			   setVSpeed(int speed);
		float			   getHSpeed(void) const;
		float			   getVSpeed(void) const;
		sf::Shape		  &getShape(void);
		sf::Text		  &getText(void);
		const sf::Vector2f getPosition(void);
		void			   setPosition(const sf::Vector2f &pos);
};
