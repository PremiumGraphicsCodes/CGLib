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

	Ellipse(const Vector2d<T>& radii, const Angle<T>& angle);

	T getArea() const;

	Vector2d<T> getCenter() const { return center; }

	Vector2d<T> getRadii() const { return radii; }

	Vector2d<T> getPosition(const Angle<T> angle) const;

	Vector2d<T> getNormal(const Angle<T> angle) const;

	Point2d<T> getPoint(const Angle<T> angle) const;

	Curve2d<T> toCurve2d(const int number) const;

	Angle<T> getAngle() const { return angle; }

	void rotate(const Angle<T>& angle) { this->angle += angle; }

private:
	Vector2d<T> radii;
	Vector2d<T> center;
	Angle<T> angle;
};
	}
}

#endif