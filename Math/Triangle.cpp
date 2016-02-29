#include "Triangle.h"

using namespace Crystal::Math;

template<typename T>
Triangle<T>::Triangle() :
	v0(Vector3d<T>(0.0, 0.0, 0.0)),
	v1(Vector3d<T>(1.0, 0.0, 0.0)),
	v2(Vector3d<T>(0.0, 1.0, 0.0))
{}

template<typename T>
Triangle<T>::Triangle(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) :
	v0(v0),
	v1(v1),
	v2(v2)
{
}

template<typename T>
Vector3d<T> Triangle<T>::getNormal() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).getNormalized();
}

template<typename T>
T Triangle<T>::getArea() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).getLength() * T(0.5);
}

template<typename T>
bool Triangle<T>::isCCW() const
{
	assert(isValid());
	return getNormal().getLength() >= 0.0f;
}

template<typename T>
bool Triangle<T>::isCW() const
{
	assert(isValid());
	return !isCCW();
}

template<typename T>
Vector3d<T> Triangle<T>::getCenter() const
{
	return (v0 + v1 + v2) / T(3);
}


template class Triangle<float>;
template class Triangle<double>;