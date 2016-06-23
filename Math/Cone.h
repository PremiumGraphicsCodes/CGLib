#ifndef __CRYSTAL_MATH_CONE_H__
#define __CRYSTAL_MATH_CONE_H__

#include "IPrimitive3d.h"

#include "Point3d.h"
#include "Param.h"
#include "Angle.h"
#include "CircularCurve3d.h"

namespace Crystal {
	namespace Math {


template<typename T>
class Cone : public IPrimitive3d<T>
{
public:
	Cone();

	Cone(const T radius, const T height);

	Cone(const T radius, const T height, const Vector3d<T>& center);

	Cone(const T radius, const T height, const Vector3d<T>& center, const Quaternion<T>& orientation);

	T getVolume() const;

	T getRadius() const { return radius; }

	T getHeight() const { return height; }

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;

	Vector3d<T> getNormal(const Angle<T> u, const Param<T> v) const;

	Vector3d<T> getNormal(const Param<T> u, const Param<T> v) const;

	Point3d<T> getPoint(const Param<T> u, const Param<T> v) const;

	CircularCurve3d<T> toSideCurve(const int num) const;

	CircularCurve3d<T> toBottomCurve(const int num) const;

private:
	T radius;
	T height;
};
	}
}

#endif