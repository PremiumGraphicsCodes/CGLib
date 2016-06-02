#ifndef __CRYSTAL_MATH_ELLIPSOID_H__
#define __CRYSTAL_MATH_ELLIPSOID_H__

#include "Vector3d.h"
#include "Angle.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Ellipsoid
{
public:
	Ellipsoid();

	Ellipsoid(const Vector3d<T>& center, const T radius);

	Ellipsoid(const Vector3d<T>& center, const Vector3d<T>& radii);

	T getVolume() const;

	Vector3d<T> getCenter() const { return center; }

	Vector3d<T> getPosition(const Angle<T> u, const Angle<T> v) const;

	Vector3d<T> getRadii() const { return radii; }

private:
	Vector3d<T> center;
	Vector3d<T> radii;
};
	}
}

#endif