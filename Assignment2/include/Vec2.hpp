#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Vec2 {
	private:
	public:
		Vec2(void);
		Vec2(float xin, float yin);
		Vec2(const Vec2 &other);
		Vec2 &operator=(const Vec2 &other);
		~Vec2(void);

		Vec2 operator+(const Vec2 &other) const;
		Vec2 operator-(const Vec2 &other) const;
		Vec2 operator*(const Vec2 &other) const;
		Vec2 operator/(const Vec2 &other) const;

		Vec2 operator*(const float scalar) const;
		Vec2 operator/(const float scalar) const;

		Vec2 &operator+=(const Vec2 &other);
		Vec2 &operator-=(const Vec2 &other);
		Vec2 &operator*=(const Vec2 &other);
		Vec2 &operator/=(const Vec2 &other);

		Vec2 &operator*=(const float scalar);
		Vec2 &operator/=(const float scalar);

		float x;
		float y;
};

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec);
Vec2		  operator*(const float scalar, const Vec2 &vec);
