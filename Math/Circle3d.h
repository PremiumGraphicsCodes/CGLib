#ifndef __CRYSTAL_MATH_CIRCLE_3D_H__
#define __CRYSTAL_MATH_CIRCLE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Circle3d
{
public:
	Circle3d();

	Circle3d(const Vector3d<T>& center, const Vector3d<T>& normal);

private:
	Vector3d<T> center;
	Vector3d<T> normal;
};
	}
}

#endif