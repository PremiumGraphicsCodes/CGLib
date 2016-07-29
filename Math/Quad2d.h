#ifndef __CRYSTAL_MATH_QUAD_2D_H__
#define __CRYSTAL_MATH_QUAD_2D_H__

#include "Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Quad2d
{
public:
	Quad2d();

	Quad2d(const Vector2d<T>& origin, const Vector2d<T>& length);

	void moveStartTo(const Vector2d<T>& start);

	void moveEndTo(const Vector2d<T>& end);

	Vector2d<T> getStart() const;

	Vector2d<T> getEnd() const;

	T getArea() const;

	bool equals(const Quad2d<T>& rhs) const;

	bool operator==(const Quad2d<T>& rhs) const;

	bool operator!=(const Quad2d<T>& rhs) const;

	Vector2d<T> getPosition(const T u, const T v) const;

	Vector2d<T> getLength() const { return length; }

	Vector2d<T> getMin() const;

	Vector2d<T> getMax() const;

private:
	Vector2d<T> origin;
	Vector2d<T> length;
};
	}
}

#endif