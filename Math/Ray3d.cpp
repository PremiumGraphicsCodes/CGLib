#include "Ray3d.h"
#include "Matrix3d.h"
#include "Triangle.h"

using namespace Crystal::Math;

template<typename T>
bool Ray3d<T>::isParallel(const Triangle<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	const Matrix3d<T> m1( edge1, edge2, -dir);
	const auto demoninator = m1.getDeterminant();

	return demoninator <= 0;
}

template<typename T>
Vector3d<T> Ray3d<T>::getParam(const Triangle<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	const Matrix3d<T> m1(edge1, edge2, -dir);
	const auto denominator = m1.getDeterminant();

	const Matrix3d<T> m2(origin - triangle.getv0(), edge2, -dir);
	const auto u = m2.getDeterminant() / denominator;

	const Matrix3d<T> m3(edge1, origin - triangle.getv0(), -dir);
	const auto v = m3.getDeterminant() / denominator;

	const Matrix3d<T> m4(edge1, edge2, origin - triangle.getv0());
	const auto t = m4.getDeterminant() / denominator;
	return Vector3d<T>(u, v, t);
}


template<typename T>
Vector3d<T> Ray3d<T>::getIntersection(const Triangle<T>& triangle) const
{
	const Vector3d<T>& p = getParam(triangle);
	return origin + dir * p.getZ();
}

/*
template<typename T>
bool Ray3d<T>::hasIntersection(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const
{
	if (isParallel()) {
		return false;
	}
	const auto u = getParamU(v0, v1, v2);
	if (u < 0 || 1 < u) {
		return false;
	}
	if (u < 0 || 1 < (u + v)) {
		return false;
	}
	return true;
}
*/

template class Ray3d<float>;
template class Ray3d<double>;