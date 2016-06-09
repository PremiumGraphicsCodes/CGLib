#ifndef __CRYSTAL_MATH_CIRCLE_3D_H__
#define __CRYSTAL_MATH_CIRCLE_3D_H__

#include "Vector3d.h"
#include "Angle.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Curve3d;

template<typename T>
class Circle3d
{
public:
	Circle3d();

	Circle3d(const T radius, const Vector3d<T>& center, const Vector3d<T>& normal);

	bool equals(const Circle3d<T>& rhs) const;

	bool operator==(const Circle3d<T>& rhs) const;

	bool operator!=(const Circle3d<T>& rhs) const;

	//Vector3d<T> getPosition(const Angle<T> angle) const;

	//Curve3d<T> toCurve3d() const;

private:
	T radius;
	Vector3d<T> center;
	Vector3d<T> normal;
};
	}
}

#endif