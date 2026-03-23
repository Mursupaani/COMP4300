#pragma once
#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

class CTransform {
	public:
		Vec2 pos = {0, 0};
		Vec2 velocity = {0, 0};
		CTransform() {};
		CTransform(const Vec2 &p, const Vec2 &v) : pos(p), velocity(v) {};
};

class CShape {
	public:
		sf::CircleShape shape;
		CShape() {};
};

class CName {
	public:
		std::string name;
		CName() {};
		CName(const std::string &n) : name(n) {};
};

class CBBox {
	public:
		CBBox() {};
};
