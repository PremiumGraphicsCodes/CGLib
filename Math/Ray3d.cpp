#include "Ray3d.h"
#include "Matrix3d.h"

using namespace Crystal::Math;

template<typename T>
bool Ray3d<T>::isParallel(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const
{
	const Vector3d<T> edge1 = v1 - v0;
	const Vector3d<T> edge2 = v2 - v0;

	const Matrix3d<T> m1( edge1, edge2, -dir);
	const auto demoninator = m1.getDeterminant();

	return demoninator <= 0;
}

template<typename T>
Vector3d<T> Ray3d<T>::getParam(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const
{
	const Vector3d<T> edge1 = v1 - v0;
	const Vector3d<T> edge2 = v2 - v0;

	const Matrix3d<T> m1(edge1, edge2, -dir);
	const auto denominator = m1.getDeterminant();

	const Matrix3d<T> m2(origin - v0, edge2, -dir);
	const auto u = m2.getDeterminant() / denominator;

	const Matrix3d<T> m3(edge1, origin - v0, -dir);
	const auto v = m3.getDeterminant() / denominator;

	const Matrix3d<T> m4(edge1, edge2, origin - v0);
	const auto t = m4.getDeterminant() / denominator;
	return Vector3d<T>(u, v, t);
}


template<typename T>
Vector3d<T> Ray3d<T>::getIntersection(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) const
{
	const Vector3d<T>& p = getParam(v0, v1, v2);
	return origin + dir * p.getZ();
}

template class Ray3d<float>;
template class Ray3d<double>;