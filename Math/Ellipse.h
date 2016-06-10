#ifndef __CRYSTAL_MATH_ELLIPSE_H__
#define __CRYSTAL_MATH_ELLIPSE_H__

#include "Curve2d.h"
#include "Angle.h"
#include "Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Ellipse
{
public:
	Ellipse();

	Ellipse(const Vector2d<T>& radii);

	T getArea() const;

	Vector2d<T> getPosition(const Angle<T> angle) const;

	Vector2d<T> getNormal(const Angle<T> angle) const;

	Point2d<T> getPoint(const Angle<T> angle) const;

	Curve2d<T> toCurve2d(const int number) const;

private:
	Vector2d<T> radii;
	Vector2d<T> center;
};
	}
}

#endif