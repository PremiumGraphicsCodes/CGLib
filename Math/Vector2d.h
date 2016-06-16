#ifndef __CRSYTAL_MATH_VECTOR_2D_H__
#define __CRSYTAL_MATH_VECTOR_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"
#include "Angle.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Vector2d final
{
public:
	Vector2d(void) : Vector2d(0, 0)
	{}

	Vector2d(const T x, const T y) :
		x(x), y(y)
	{}

	T getX() const { return x; }

	T getY() const { return y; }

	T getDistanceSquared(const Vector2d& rhs) const;

	T getLengthSquared() const;

	T getLength() const;

	bool equals(const Vector2d& rhs) const {
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	void scale(const T scale) {
		x *= scale;
		y *= scale;
	}

	bool operator==(const Vector2d& rhs) const { return equals(rhs); }

	bool operator!=(const Vector2d& rhs) const { return !equals(rhs); }

	Vector2d operator+(const Vector2d& rhs) const { return Vector2d(x + rhs.x, y + rhs.y); }

	Vector2d operator-(const Vector2d& rhs) const { return Vector2d(x - rhs.x, y - rhs.y); }

	Vector2d& operator+=(const Vector2d& rhs) {
		this->x += rhs.x; this->y += rhs.y;
		return *this;
	}

	Vector2d<T> normalize();

	Vector2d<T> getNormalized() const;

	Angle<T> getAngle() const;

private:
	T x;
	T y;
};
	}
}

#endif