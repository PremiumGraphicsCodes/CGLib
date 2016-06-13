#include "PolarCoord3d.h"

using namespace Crystal::Math;

template<typename T>
PolarCoord3d<T>::PolarCoord3d() :
	length(1),
	azimuth(Radian<T>(0)),
	elevation(Radian<T>(0))
{}

template<typename T>
PolarCoord3d<T>::PolarCoord3d(const T length, const Angle<T> azimuth, const Angle<T> elevation) :
	length(length),
	azimuth(azimuth),
	elevation(elevation)
{
//	assert(isValid());
}

template<typename T>
Vector3d<T> PolarCoord3d<T>::toOrtho() const
{
	const auto x = length * azimuth.getSin() * elevation.getCos();
	const auto y = length * azimuth.getSin() * elevation.getSin();
	const auto z = length * azimuth.getCos();
	return Vector3d<T>(x, y, z);
}

template<typename T>
Matrix3d<T> PolarCoord3d<T>::toMatrix() const
{
	Matrix3d<T> m1 = Matrix3d<T>::RotateZ(elevation.getRadian().get());
	Matrix3d<T> m2 = Matrix3d<T>::RotateY(azimuth.getRadian().get());
	return m1 * m2;
}

template<typename T>
Quaternion<T> PolarCoord3d<T>::toQuaternion() const
{
	Quaternion<T> q1(Vector3d<T>(0, 1, 0), azimuth.getRadian().get());
	Quaternion<T> q2(Vector3d<T>(0, 0, 1), elevation.getRadian().get());

	/*
	Quaternion<T> q1(Vector3d<T>(0, 0, 1), elevation.getRadian().get());
	Quaternion<T> q2(Vector3d<T>(1, 0, 0), azimuth.getRadian().get());
	*/
	return q1 * q2;
}

template<typename T>
bool PolarCoord3d<T>::equals(const PolarCoord3d<T>& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(this->length, rhs.length) &&
		azimuth == rhs.azimuth &&
		elevation == rhs.elevation;
}

template<typename T>
bool PolarCoord3d<T>::operator==(const PolarCoord3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool PolarCoord3d<T>::operator!=(const PolarCoord3d<T>& rhs) const
{
	return !equals(rhs);
}

template<typename T>
bool PolarCoord3d<T>::isValid() const
{
	bool azimuthIsValid = (T{ 0 } <= azimuth.getDegree().get() && azimuth.getDegree().get() <= T{ 360 });
	bool elevationIsValid = (T{ -90 } <= elevation.getDegree().get() && elevation.getDegree().get() <= T{ 90 } );
	return azimuthIsValid && elevationIsValid;
}


template class PolarCoord3d<float>;
template class PolarCoord3d<double>;