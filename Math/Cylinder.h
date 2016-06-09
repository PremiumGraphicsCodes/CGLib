#ifndef __CRYSTAL_MATH_CYLINDER_H__
#define __CRYSTAL_MATH_CYLINDER_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Param.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Cylinder
{
public:
	Cylinder();

	Cylinder(const Vector3d<T>& center, const T radius, const T height);

	T getVolume() const;

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;
	
	//T getRadius() const;

private:
	T radius;
	T height;
	Vector3d<T> center;
};
	}
}

#endif