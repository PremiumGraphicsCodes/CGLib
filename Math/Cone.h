#ifndef __CRYSTAL_MATH_CONE_H__
#define __CRYSTAL_MATH_CONE_H__

#include "Vector3d.h"
#include "Param.h"
#include "Angle.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Cone
{
public:
	Cone();

	Cone(const T radius, const T height);

	T getVolume() const;

	T getRadius() const { return radius; }

	T getHeight() const { return height; }

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Vector3d<T> getPosition(const Angle<T> u, const Param<T> v) const;

private:
	Math::Vector3d<T> center;
	T radius;
	T height;
};
	}
}

#endif