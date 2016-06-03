#include "PolarCoord3d.h"

using namespace Crystal::Math;

template<typename T>
PolarCoord3d<T>::PolarCoord3d() :
	length(1),
	theta(Radian<T>(0)),
	phi(Radian<T>(0))
{}

template<typename T>
PolarCoord3d<T>::PolarCoord3d(const T length, const Angle<T> theta, const Angle<T> phi) :
	length(length),
	theta(theta),
	phi(phi)
{}

template<typename T>
PolarCoord3d<T>::PolarCoord3d(const Vector3d<T>& v) :
	length(v.getLength()),
	theta(Radian<T>(std::acos(v.getZ() / v.getLength())))
{
	const auto denominator = std::sqrt(v.getX() * v.getX() + v.getY() * v.getY());
	if (Tolerance<T>::isEqualLoosely(denominator, 0)) {
		phi = Angle<T>( Radian<T>(0) );
	}
	else {
		phi = Angle<T>( Radian<T>(std::acos(v.getX() / denominator ) ) );
	}
}

template<typename T>
Vector3d<T> PolarCoord3d<T>::toOrtho() const
{
	const auto x = length * theta.getSin() * phi.getCos();
	const auto y = length * theta.getSin() * phi.getSin();
	const auto z = length * theta.getCos();
	return Vector3d<T>(x, y, z);
}

template<typename T>
Matrix3d<T> PolarCoord3d<T>::toMatrix() const
{
	Matrix3d<T> m1 = Matrix3d<T>::RotateZ(phi.getRadian().get());
	Matrix3d<T> m2 = Matrix3d<T>::RotateY(theta.getRadian().get());
	return m1 * m2;
}

template<typename T>
Quaternion<T> PolarCoord3d<T>::toQuaternion() const
{
	Quaternion<T> q1(Vector3d<T>(0, 0, 1), phi.getRadian().get());
	Quaternion<T> q2(Vector3d<T>(1, 0, 0), theta.getRadian().get());
	return q1 * q2;
}

template<typename T>
bool PolarCoord3d<T>::equals(const PolarCoord3d<T>& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(this->length, rhs.length) &&
		theta == rhs.theta &&
		phi == rhs.phi;
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


template class PolarCoord3d<float>;
template class PolarCoord3d<double>;