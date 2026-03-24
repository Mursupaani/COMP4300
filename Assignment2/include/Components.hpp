#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Vec2.hpp"

class CTransform {
	public:
		Vec2  pos = {0, 0};
		Vec2  velocity = {0, 0};
		float angle = 0;

		CTransform(const Vec2 &p, const Vec2 &v, const float angle)
			: pos(p), velocity(v), angle(angle) {};
};

class CShape {
	public:
		sf::CircleShape circle;
		CShape(const float radius, const int points, const sf::Color &fill,
			   const sf::Color &outline, const float thickness)
			: circle(radius, points) {
			circle.setFillColor(fill);
			circle.setOutlineColor(outline);
			circle.setOutlineThickness(thickness);
			circle.setOrigin(sf::Vector2f(radius, radius));
		};
};

class CCollision {
	public:
		float radius = 0;
		CCollision(const float r) : radius(r) {};
};

class CScore {
	public:
		unsigned int score = 0;
		CScore(const int s) : score(s) {};
};

class CLifespan {
	public:
		int remaining = 0;
		int total = 0;
		CLifespan(const int total) : remaining(total), total(total) {};
};

class CInput {
	public:
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		bool shoot = false;
		CInput() {};
};
