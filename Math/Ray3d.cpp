#include "Ray3d.h"
#include "Matrix3d.h"
#include "Triangle3d.h"
#include "Sphere.h"

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
Vector3d<T> Ray3d<T>::getParam(const Triangle3d<T>& triangle) const
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
	const auto& param = getParam(triangle);
	if (param.getX() < 0 || 1 < param.getX()) {
		return false;
	}
	if (param.getX() < 0 || 1 < (param.getX() + param.getY())) {
		return false;
	}
	return true;
}

template<typename T>
bool Ray3d<T>::hasIntersection(const Sphere<T>& sphere) const
{
	const auto a = dir.getLengthSquared();
	const auto b = sphere.getCenter().getInnerProduct(dir);
	const auto c = sphere.getCenter().getLengthSquared() - sphere.getRadius() * sphere.getRadius();
	const auto d = (b*b - a*c);
	return d >= 0;
}

template<typename T>
std::vector<Vector3d<T>> Ray3d<T>::getIntersections(const Sphere<T>& sphere) const
{
	const auto v = sphere.getCenter() - origin;
	const auto a = dir.getLengthSquared();
	const auto b = v.getInnerProduct(dir);
	const auto c = v.getLengthSquared() - sphere.getRadius() * sphere.getRadius();
	const auto d = (b*b - a*c);
	if (d < 0) {
		return{};
	}
	const auto a1 = (b - d) / a;
	const auto a2 = (b + d) / a;
	Vector3d<T> i1 = origin + a1 * dir;
	Vector3d<T> i2 = origin + a2 * dir;
	return{ i1,i2 };
}


template class Ray3d<float>;
template class Ray3d<double>;