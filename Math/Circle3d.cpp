#include "Circle3d.h"

using namespace Crystal::Math;

template<typename T>
Circle3d<T>::Circle3d():
	radius(0.5),
	normal(Vector3d<T>(0,0,1))
{
}

template<typename T>
Circle3d<T>::Circle3d(const T radius,const Vector3d<T>& center, const Vector3d<T>& normal) :
	radius(radius),
	center(center),
	normal(normal)
{
}

template<typename T>
bool Circle3d<T>::equals(const Circle3d<T>& rhs) const
{
	return
		radius == rhs.radius &&
		center == rhs.center &&
		normal == rhs.normal;
}

template<typename T>
bool Circle3d<T>::operator==(const Circle3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Circle3d<T>::operator!=(const Circle3d<T>& rhs) const
{
	return !equals(rhs);
}

/*
template<typename T>
Vector3d<T> Circle3d<T>::getPosition(const Angle<T> angle) const
{
	const auto x = radius * angle.getSin();
	const auto y = radius * angle.getCos();
	return Vector3d<T>(x, y, 0);
}


template<typename T>
Curve3d<T> Circle3d<T>::toCurve3d() const
{
	;
}
*/


template class Circle3d<float>;
template class Circle3d<double>;