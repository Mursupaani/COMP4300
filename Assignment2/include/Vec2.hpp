#pragma once
#include <cmath>
#include <iostream>
#include <ostream>
#define DEG2RAD(deg) (M_PI / 180)

// NOTE: To implement: length, normalize, rotate, etc?

class Vec2 {
	private:
		static constexpr float _epsilon = 1E-8;

	public:
		float x;
		float y;

		Vec2(void);
		Vec2(float xin, float yin);
		Vec2(const Vec2 &other);
		Vec2 &operator=(const Vec2 &other);
		~Vec2(void);

		float length(void) const;
		float dist(const Vec2 &other) const;
		Vec2 &add(const Vec2 &other);
		Vec2 &normalize(void);

		Vec2 &scale(const float scalar);
		Vec2 &rotate(const float deg);

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

		bool operator==(const Vec2 &other) const;
		bool operator!=(const Vec2 &other) const;
};

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec);
Vec2		  operator*(const float scalar, const Vec2 &vec);
