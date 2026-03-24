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

float Vec2::length(void) const {
	return (sqrtf(x * x + y * y));
	return (0);
}

Vec2 &Vec2::add(const Vec2 &other) {
	x += other.x;
	y += other.y;
	return (*this);
}

Vec2 &Vec2::normalize(void) {
	float len = this->length();
	x /= len;
	y /= len;
	return (*this);
}

Vec2 &Vec2::scale(const float scalar) {
	x *= scalar;
	y *= scalar;
	return (*this);
}

Vec2 &Vec2::rotate(const float deg) {
	float theta = deg * (M_PI / 180);
	float cosTheta = std::cos(theta);
	float sinTheta = std::sin(theta);
	float oldX = x;
	x = oldX * cosTheta - y * sinTheta;
	y = oldX * sinTheta + y * cosTheta;
	return (*this);
}

float Vec2::dist(const Vec2 &other) const {
	return (sqrtf(powf(other.x - x, 2) + powf(other.y - y, 2)));
}

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

bool Vec2::operator==(const Vec2 &other) const {
	return ((fabs(x - other.x) <= _epsilon) && fabs(y - other.y) <= _epsilon);
}

bool Vec2::operator!=(const Vec2 &other) const {
	return (*this == other);
}
Vec2 operator*(const float scalar, const Vec2 &vec) {
	return (Vec2(scalar * vec.x, scalar * vec.y));
}

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec) {
	return (stream << "{" << vec.x << ", " << vec.y << "}");
}
