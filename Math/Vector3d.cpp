#include "Vector3d.h"

using namespace Crystal::Math;

template<typename T>
Vector3d<T>& Vector3d<T>::scale(const T factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

template<typename T>
Vector3d<T>& Vector3d<T>::scale(const T xFactor, const T yFactor, const T zFactor)
{
	x *= xFactor;
	y *= yFactor;
	z *= zFactor;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::normalize()
{
	const auto length = getLength();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::getNormalized() const
{
	Vector3d<T> vector = *(this);
	return vector.normalize();
}

template<typename T>
Vector3d<T> Vector3d<T>::operator+=(const Vector3d& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::operator-=(const Vector3d& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}


template class Vector3d<float>;
template class Vector3d<double>;