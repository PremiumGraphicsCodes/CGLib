#ifndef __CRYSTAL_MATH_CYLINDROID_H__
#define __CRYSTAL_MATH_CYLINDROID_H__

#include "Param.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "Curve3d.h"
#include "CircularCurve3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Cylindroid
{
public:
	Cylindroid();

	Cylindroid(const Vector3d<T>& center, const Vector2d<T>& radii, const T height);

	T getVolume() const;

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;

	/*
	Vector3d<T> getNormal(const Param<T> u, const Param<T> v) const;

	Point3d<T> getPoint(const Param<T> u, const Param<T> v) const;

	CircularCurve3d<T> getTopCurve(const int number) const;

	CircularCurve3d<T> getBottomCurve(const int number) const;

	Curve3d<T> getSideCurve(const int number) const;
	*/
private:
	Vector3d<T> center;
	Vector2d<T> radii;
	T height;
};
	}
}

#endif