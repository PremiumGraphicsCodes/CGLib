#ifndef __CRYSTAL_MATH_BOX_2D_H__
#define __CRYSTAL_MATH_BOX_2D_H__

#include "Vector2d.h"

namespace Crystal {
	namespace Math {
	
template<typename T>
class Box2d
{
public:
	Box2d();

	Box2d(const Vector2d<T>& pointX, const Vector2d<T>& pointY);

	void add(const Vector2d<T>& v);

	void add(const Box2d& b);

	T getArea() const;

	Vector2d<T> getMax() const { return Vector2d<T>(end.getX(), end.getY()); }

	Vector2d<T> getMin() const { return Vector2d<T>(getMinX(), getMinY()); }

	Vector2d<T> getStart() const { return getMin(); }

	Vector2d<T> getEnd() const { return getMax(); }

	Vector2d<T> getCenter() const;

	//std::vector< Vector2d<T> > toInnerPoints(const T divideLength) const;

	T getMaxX() const { return end.getX(); }

	T getMinX() const { return start.getX(); }

	T getMaxY() const { return end.getY(); }

	T getMinY() const { return start.getY(); }

	Vector2d<T> getLength() const {
		return Vector2d<T>(end.getX() - getMinX(), end.getY() - getMinY());
	}

	bool isValid() const;

	bool isShirinked() const;

	bool equals(const Box2d& rhs) const;

	bool operator==(const Box2d& rhs) const { return equals(rhs); }

	bool operator!=(const Box2d& rhs) const { return !equals(rhs); }

	bool hasIntersection(const Box2d& rhs) const;

	Box2d getOverlapped(const Box2d& rhs) const;

	//Space3d<T> toSpace() const;

private:
	Vector2d<T> start;
	Vector2d<T> end;
};

	}
}

#endif