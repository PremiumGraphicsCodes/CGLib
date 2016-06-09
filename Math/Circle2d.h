#ifndef __CRYSTAL_MATH_CIRCLE_2D_H__
#define __CRYSTAL_MATH_CIRCLE_2D_H__

#include "Vector2d.h"
#include "Angle.h"
#include "Point2d.h"
#include "Curve2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Circle2d
{
public:
	Circle2d();

	explicit Circle2d(const T radius);

	T getArea() const;

	//std::vector<Vector2d<T>> toPoints(const int number) const;

	Vector2d<T> getPosition(const Angle<T> angle) const;

	Vector2d<T> getNormal(const Angle<T> angle) const;

	Point2d<T> getPoint(const Angle<T> angle) const;

	Curve2d<T> toCurve2d(const int number) const;

private:
	T radius;
	Vector2d<T> center;
};
	}
}

#endif