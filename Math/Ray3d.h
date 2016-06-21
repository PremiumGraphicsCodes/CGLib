#ifndef __CRYSTAL_MATH_RAY_3D_H__
#define __CRYSTAL_MATH_RAY_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Ray3d
{
public:
	Ray3d() = default;

	Ray3d(const Vector3d<T>& origin, const Vector3d<T>& dir) :
		origin(origin),
		dir(dir)
	{}

	//bool hasIntersection(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const;

	bool isParallel(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const;

	Vector3d<T> getParam(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const;

	Vector3d<T> getIntersection(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const;
	
private:
	Vector3d<T> origin;
	Vector3d<T> dir;
};
	}
}

#endif