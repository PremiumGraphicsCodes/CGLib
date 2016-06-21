#include "Ray3d.h"
#include "Matrix3d.h"
#include "Triangle3d.h"

using namespace Crystal::Math;

template<typename T>
bool Ray3d<T>::isParallel(const Triangle3d<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	//const Matrix3d<T> m1( edge1, edge2, -dir);
	const auto v = -dir.getOuterProduct(edge2);
	const auto det = v.getInnerProduct(edge1);

	return det < Tolerance<T>::getLooseTolerance();;
}

template<typename T>
T Ray3d<T>::getParamU(const Triangle3d<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	const Matrix3d<T> m1(edge1, edge2, -dir);
	const auto denominator = m1.getDeterminant();

	const Matrix3d<T> m2(origin - triangle.getv0(), edge2, -dir);
	return m2.getDeterminant() / denominator;
}

template<typename T>
T Ray3d<T>::getParamV(const Triangle3d<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	const Matrix3d<T> m1(edge1, edge2, -dir);
	const auto denominator = m1.getDeterminant();

	const Matrix3d<T> m3(edge1, origin - triangle.getv0(), -dir);
	return m3.getDeterminant() / denominator;
}



template<typename T>
Vector3d<T> Ray3d<T>::getParam(const Triangle3d<T>& triangle) const
{
	const Vector3d<T> edge1 = triangle.getv1() - triangle.getv0();
	const Vector3d<T> edge2 = triangle.getv2() - triangle.getv0();

	const Matrix3d<T> m1(edge1, edge2, -dir);
	const auto denominator = m1.getDeterminant();

	const auto u = getParamU(triangle);
	const auto v = getParamV(triangle);

	const Matrix3d<T> m4(edge1, edge2, origin - triangle.getv0());
	const auto t = m4.getDeterminant() / denominator;
	return Vector3d<T>(u, v, t);
}


template<typename T>
Vector3d<T> Ray3d<T>::getIntersection(const Triangle3d<T>& triangle) const
{
	const Vector3d<T>& p = getParam(triangle);
	return origin + dir * p.getZ();
}

template<typename T>
bool Ray3d<T>::hasIntersection(const Triangle3d<T>& triangle) const
{
	if (isParallel(triangle)) {
		return false;
	}
	const auto u = getParamU(triangle);
	if (u < 0 || 1 < u) {
		return false;
	}
	const auto v = getParamV(triangle);
	if (u < 0 || 1 < (u + v)) {
		return false;
	}
	return true;
}

template class Ray3d<float>;
template class Ray3d<double>;