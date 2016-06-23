#ifndef __CRYSTAL_MATH_CYLINDER_H__
#define __CRYSTAL_MATH_CYLINDER_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Param.h"
#include "Point3d.h"
#include "CircularCurve3d.h"
#include "IPrimitive3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Circle3d;
		template<typename T>
		class Curve3d;

template<typename T>
class Cylinder : public IPrimitive3d<T>
{
public:
	Cylinder();

	Cylinder(const Vector3d<T>& center, const T radius, const T height);

	Cylinder(const Vector3d<T>& center, const T radius, const T height, const Quaternion<T>& quaternion);

	T getVolume() const;

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;

	Vector3d<T> getNormal(const Param<T> u, const Param<T> v) const;

	Point3d<T> getPoint(const Param<T> u, const Param<T> v) const;
	
	Circle3d<T> getBotton() const;

	Circle3d<T> getTop() const;

	CircularCurve3d<T> getTopCurve(const int number) const;

	CircularCurve3d<T> getBottomCurve(const int number) const;

	Curve3d<T> getSideCurve(const int number) const;

	std::vector< Curve3d<T> > toCurve3ds(int number) const;
	//T getRadius() const;

	void move(const Vector3d<T>& v) { this->center += v; }

	bool equals(const Cylinder<T>& rhs) const;

	bool operator==(const Cylinder<T>& rhs) const;

	bool operator!=(const Cylinder<T>& rhs) const;

private:
	T radius;
	T height;
};
	}
}

#endif