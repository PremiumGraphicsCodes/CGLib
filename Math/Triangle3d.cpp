#include "Triangle3d.h"

using namespace Crystal::Math;

template<typename T>
Triangle3d<T>::Triangle3d() :
	v0(Vector3d<T>(0.0, 0.0, 0.0)),
	v1(Vector3d<T>(1.0, 0.0, 0.0)),
	v2(Vector3d<T>(0.0, 1.0, 0.0))
{}

template<typename T>
Triangle3d<T>::Triangle3d(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) :
	v0(v0),
	v1(v1),
	v2(v2)
{
}

template<typename T>
Vector3d<T> Triangle3d<T>::getNormal() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).getNormalized();
}

template<typename T>
T Triangle3d<T>::getArea() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).getLength() * T(0.5);
}

template<typename T>
bool Triangle3d<T>::isCCW() const
{
	assert(isValid());
	return getNormal().getLength() >= 0.0f;
}

template<typename T>
bool Triangle3d<T>::isCW() const
{
	assert(isValid());
	return !isCCW();
}

template<typename T>
Vector3d<T> Triangle3d<T>::getCenter() const
{
	return (v0 + v1 + v2) / T(3);
}

template<typename T>
bool Triangle3d<T>::equals(const Triangle3d<T>& rhs) const
{
	return
		v0 == rhs.v0 &&
		v1 == rhs.v1 &&
		v2 == rhs.v2;
}

template<typename T>
bool Triangle3d<T>::operator==(const Triangle3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Triangle3d<T>::operator!=(const Triangle3d<T>& rhs) const
{
	return !equals(rhs);
}



template class Triangle3d<float>;
template class Triangle3d<double>;