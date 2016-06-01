#include "Cylinder.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cylinder<T>::Cylinder() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cylinder<T>::Cylinder(const Vector3d<T>& center, const T radius, const T height) :
	center(center),
	radius(radius),
	height(height)
{
}

template<typename T>
T Cylinder<T>::getVolume() const
{
	return radius * radius * Tolerance<T>::getPI() * height;
}

template<typename T>
Vector3d<T> Cylinder<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return getPosition(u.toAngle(), v);
}

template<typename T>
Vector3d<T> Cylinder<T>::getPosition(const Angle<T> u, const Param<T> v) const
{
	const auto x = u.getCos();
	const auto y = u.getSin();
	const auto z = v.get() * height;
	return Vector3d<T>(x, y, z);
}


/*
template<typename T>
T Cylinder<T>::getRadius() const
{

}
*/

template class Cylinder<float>;
template class Cylinder<double>;