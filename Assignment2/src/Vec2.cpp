#include "Vec2.hpp"

Vec2::Vec2(void) : x(0.0f), y(0.0f) {}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

Vec2::Vec2(const Vec2 &other) : x(other.x), y(other.y) {}

Vec2 &Vec2::operator=(const Vec2 &other) {
	if (this == &other)
		return (*this);
	x = other.x;
	y = other.y;
	return (*this);
}
Vec2::~Vec2(void) {}

Vec2 Vec2::operator+(const Vec2 &other) const {
	return (Vec2(x + other.x, y + other.y));
}
Vec2 Vec2::operator-(const Vec2 &other) const {
	return (Vec2(x - other.x, y - other.y));
}
Vec2 Vec2::operator*(const Vec2 &other) const {
	return (Vec2(x * other.x, y * other.y));
}
Vec2 Vec2::operator/(const Vec2 &other) const {
	return (Vec2(x / other.x, y / other.y));
}

Vec2 Vec2::operator*(const float scalar) const {
	return (Vec2(x * scalar, y * scalar));
}
Vec2 Vec2::operator/(const float scalar) const {
	return (Vec2(x / scalar, y / scalar));
}
Vec2 &Vec2::operator+=(const Vec2 &other) {
	x += other.x;
	y += other.y;
	return (*this);
}
Vec2 &Vec2::operator-=(const Vec2 &other) {
	x -= other.x;
	y -= other.y;
	return (*this);
}
Vec2 &Vec2::operator*=(const Vec2 &other) {
	x *= other.x;
	y *= other.y;
	return (*this);
}
Vec2 &Vec2::operator/=(const Vec2 &other) {
	x /= other.x;
	y /= other.y;
	return (*this);
}
Vec2 &Vec2::operator*=(const float scalar) {
	x *= scalar;
	y *= scalar;
	return (*this);
}

Vec2 &Vec2::operator/=(const float scalar) {
	x /= scalar;
	y /= scalar;
	return (*this);
}

Vec2 operator*(const float scalar, const Vec2 &vec) {
	return (Vec2(scalar * vec.x, scalar * vec.y));
}

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec) {
	return (stream << "{" << vec.x << ", " << vec.y << "}");
}
