#ifndef __CRYSTAL_MATH_RAY_3D_H__
#define __CRYSTAL_MATH_RAY_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Triangle3d;
		template<typename>
		class Sphere;

template<typename T>
class Ray3d
{
public:
	Ray3d() :
		origin(Vector3d<T>(0,0,0)),
		dir(Vector3d<T>(1,0,0))
	{}

	Ray3d(const Vector3d<T>& origin, const Vector3d<T>& dir) :
		origin(origin),
		dir(dir.normalized())
	{}

	bool isParallel(const Triangle3d<T>& triangle) const;

	Vector3d<T> getParam(const Triangle3d<T>& triangle) const;

	bool hasIntersection(const Triangle3d<T>& triangle) const;

	Vector3d<T> getIntersection(const Triangle3d<T>& triangle) const;

	bool hasIntersection(const Sphere<T>& sphere) const;

	std::vector<Vector3d<T>> getIntersections(const Sphere<T>& sphere) const;
	
private:
	Vector3d<T> origin;
	Vector3d<T> dir;
};
	}
}

#endif