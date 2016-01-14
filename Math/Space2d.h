#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Space2d
{
public:
	Space2d() = default;

	explicit Space2d(const Vector2d<T>& origin) :
		origin(origin)
	{}

	Space2d(const Vector2d<T>& origin, const Vector2d<T>& length) :
		origin(origin),
		vector(length)
	{}

	~Space2d() = default;

	Vector2d<T> getStart() const { return origin; }

	Vector2d<T> getLengths() const { return vector; }

	T getArea() const { return vector.getX() * vector.getY(); }

	bool isIn(const Vector2d<T>& point) const;

	bool equals(const Space2d& rhs) const;

	bool operator==(const Space2d& rhs) const { return equals(rhs); }

	bool operator!=(const Space2d& rhs) const { return !equals(rhs); }

private:
	Vector2d<T> origin;
	Vector2d<T> vector;
};
	}
}

#endif