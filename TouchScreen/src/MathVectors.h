#ifndef MATHVECTORS_H
#define MATHVECTORS_H
#include <cmath>
#include "MathMacros.h"

class Vec2 {
public:
	Vec2(double x, double y) { this->x = x; this->y = y; }
	Vec2(double xy) { this->x = this->y = xy; }
	Vec2() { this->x = this->y = 0.0; }

	double x, y;

	inline Vec2& operator=(const Vec2& other) { this->x = other.x; this->y = other.y; return *this; }
	inline bool operator==(const Vec2& other) { return this->x == other.x && this->y == other.y; }
	inline bool operator!=(const Vec2& other) { return this->x != other.x || this->y != other.y; }

	inline Vec2 operator+(const Vec2 other) const { return Vec2(this->x + other.x, this->y + other.y); }
	inline Vec2& operator+=(const Vec2 other) { this->x += other.x; this->y += other.y; return *this; }

	inline Vec2 operator-() { return Vec2(this->x = -this->x, this->y = this->y); }
	inline Vec2 operator-(const Vec2 other) const { return Vec2(this->x - other.x, this->y - other.y); }
	inline Vec2& operator-=(const Vec2 other) { this->x -= other.x; this->y -= other.y; }

	inline Vec2 operator*(double scalar) const { return Vec2(this->x * scalar, this->y * scalar); }
	inline Vec2& operator*=(double scalar) { this->x *= scalar; this->y *= scalar; return *this; }

	inline Vec2 operator/(double scalar) const { return Vec2(this->x / scalar, this->y / scalar); }
	inline Vec2& operator/=(double scalar) { this->x /= scalar; this->y /= scalar; return *this; }

	inline double SqrMagnitude() { return x * x + y * y; }
	inline double Magnitude() { return sqrt(SqrMagnitude()); }
	inline Vec2 rotate(double angle) {
		Vec2 oldVec = *this;
		double rad = angle * 0.0174533;
		this->x = oldVec.x * cos(rad) - oldVec.y * sin(rad);
		this->y = oldVec.y * cos(rad) + oldVec.x * sin(rad);
		return *this;
	}

	inline static Vec2 LerpUnclamped(Vec2 from, Vec2 to, double value) { return MM_LERPUNCLAMPED(from, to, value); }
	inline static Vec2 Lerp(Vec2 from, Vec2 to, double value) { return MM_LERP(from, to, value); }

	inline double angle() { return atan2(y, x) * 57.2958; }
	inline static double angleBetween(Vec2 vec1, Vec2 vec2) { return abs(vec1.angle() - vec2.angle()); }
	inline double dot(const Vec2& other) { return (this->x * other.x + this->y * other.y); }
};

#define VEC2_UP (Vec2(0.0, 1.0))
#define VEC2_RIGHT (Vec2(1.0, 0.0))
#define VEC2_ONE (Vec2(1.0))
#define VEC2_ZERO (Vec2())

#endif
