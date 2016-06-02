#include "Ellipsoid.h"

using namespace Crystal::Math;

template<typename T>
Ellipsoid<T>::Ellipsoid() :
	center( 0, 0, 0),
	radii( 0.5, 0.5, 0.5 )
{}

template<typename T>
Ellipsoid<T>::Ellipsoid(const Vector3d<T>& center, const T radius) :
	center( center ),
	radii(radius, radius, radius)
{
}

template<typename T>
Ellipsoid<T>::Ellipsoid(const Vector3d<T>& center, const Vector3d<T>& radii) :
	center( center ),
	radii( radii )
{
}

template<typename T>
T Ellipsoid<T>::getVolume() const
{
	return T{ 4 } / T{ 3 } * Tolerance<T>::getPI() * radii.getX() * radii.getY() * radii.getZ();
}

template<typename T>
Vector3d<T> Ellipsoid<T>::getPosition(const Angle<T> u, const Angle<T> v) const
{
	assert(0.0 < u.getDegree().get() && u.getDegree().get() < 180.0);
	assert(0.0 < v.getDegree().get() && v.getDegree().get() < 360.0);

	const T x = radii.getX() * u.getSin() * v.getCos();
	const T y = radii.getY() * u.getSin() * v.getCos();
	const T z = radii.getZ() * u.getCos();
	return Vector3d<T>(x, y, z);
}

template class Ellipsoid<float>;
template class Ellipsoid<double>;