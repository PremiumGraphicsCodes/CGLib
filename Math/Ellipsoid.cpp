#include "Ellipsoid.h"
#include "Curve3d.h"

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
	assert(radii.getX() > T{ 0 });
	assert(radii.getY() > T{ 0 });
	assert(radii.getZ() > T{ 0 });
}

template<typename T>
T Ellipsoid<T>::getVolume() const
{
	return T{ 4 } / T{ 3 } * Tolerance<T>::getPI() * radii.getX() * radii.getY() * radii.getZ();
}

template<typename T>
Vector3d<T> Ellipsoid<T>::getPosition(const Angle<T> u, const Angle<T> v) const
{
	assert(0.0 <= u.getDegree().get() && u.getDegree().get() <= 360.0);
	assert(-90.0 <= v.getDegree().get() && v.getDegree().get() <= 90.0);

	const T x = radii.getX() * u.getCos() * v.getCos();
	const T y = radii.getY() * u.getSin() * v.getCos();
	const T z = radii.getZ() * v.getSin();
	/*
	const T x = radii.getX() * u.getSin() * v.getCos();
	const T y = radii.getY() * u.getSin() * v.getSin();
	const T z = radii.getZ() * v.getCos();
	*/
	return Vector3d<T>(x, y, z) + center;
}

template<typename T>
Curve3d<T> Ellipsoid<T>::toCurve3d(const int uNum, const int vNum) const
{
	Curve3d<T> curve(uNum, vNum);
	const auto du = 360.0f / static_cast<T>(uNum);
	const auto dv = 180.0f / static_cast<T>(vNum);
	for (int i = 0; i < uNum; ++i){
		for (int j = 0; j < vNum; ++j) {
			const Degree<T> uAngle(du * i);
			const Degree<T> vAngle(dv * j - 90.0f);
			const auto& pos = getPosition(Angle<T>(uAngle), Angle<T>(vAngle));
			const Point3d<T> point(pos);
			curve.set(i, j, point);
		}
	}
	return curve;
}


template class Ellipsoid<float>;
template class Ellipsoid<double>;