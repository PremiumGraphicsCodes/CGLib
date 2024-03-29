#ifndef __CRYSTAL_MATH_CYLINDROID_H__
#define __CRYSTAL_MATH_CYLINDROID_H__

#include "Param.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "Curve3d.h"
#include "CircularCurve3d.h"
#include "Quaternion.h"
#include "IPrimitive3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Cylindroid : public IPrimitive3d<T>
{
public:
	Cylindroid();

	Cylindroid(const Vector3d<T>& center, const Vector2d<T>& radii, const T height);

	Cylindroid(const Vector3d<T>& center, const Vector2d<T>& radii, const T height, const Quaternion<T>& orientation);

	T getVolume() const;

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;

	Vector3d<T> getNormal(const Param<T> u, const Param<T> v) const;

	Point3d<T> getPoint(const Param<T> u, const Param<T> v) const;

	//Point3d<T> getPoint(const Angle<T> u, const Param<T> v) const;

	/*
	CircularCurve3d<T> getTopCurve(const int number) const;

	CircularCurve3d<T> getBottomCurve(const int number) const;
	*/
	Curve3d<T> getSideCurve(const int number) const;

	Cylindroid<T> scaled(const Vector2d<T>& radiiScale, const T heightScale) const;

private:
	Vector2d<T> radii;
	T height;
};
	}
}

#endif