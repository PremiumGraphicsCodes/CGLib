#include "Cone.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cone<T>::Cone() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height) :
	radius(radius),
	height(height)
{}

template<typename T>
T Cone<T>::getVolume() const
{
	return Tolerance<T>::getPI() * radius * radius * height / T{ 3 };
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return getPosition(u.toAngle(), v);
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Angle<T> u, const Param<T> v) const
{
	const auto x = radius * (1-v.get()) * u.getCos();
	const auto y = v.get() * height;
	const auto z = radius * (1-v.get()) * u.getSin();

	return Vector3d<T>(x, y, z) + Vector3d<T>(0, -height*T{ 0.5 }, 0) + center;
}


template class Cone<float>;
template class Cone<double>;