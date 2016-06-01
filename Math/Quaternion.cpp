#include "Quaternion.h"

#include "Matrix3d.h"
#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Quaternion<T>::Quaternion(void) :
	x(0.0), y(0.0), z(0.0), w(1.0)
{
}

template<typename T>
Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) :
	x(x), y(y), z(z), w(w)
{
}

template<typename T>
Quaternion<T>::Quaternion(const Vector3d<T>& axis, const T angle) :
	x(axis.getX() * sin(angle * 0.5f)),
	y(axis.getY() * sin(angle * 0.5f)),
	z(axis.getZ() * sin(angle * 0.5f)),
	w(cos(angle * 0.5f))
{
	assert(axis.isNormalized());
}

template<typename T>
Matrix3d<T> Quaternion<T>::toMatrix() const
{
	const auto x00 = (1.0f - 2.0f * y * y - 2.0f * z * z);
	const auto x01 = (2.0f * x * y - 2.0f * z * w);
	const auto x02 = (2.0f * x * z + 2.0f * y * w);

	const auto x10 = (2.0f * x * y + 2.0f * z * w);
	const auto x11 = (1.0f - 2.0f * x * x - 2.0f * z * z);
	const auto x12 = (2.0f * y * z - 2.0f * x * w);

	const auto x20 = (2.0f * x * z - 2.0f * y * w);
	const auto x21 = (2.0f * y * z + 2.0f * x * w);
	const auto x22 = (1.0f - 2.0f * x * x - 2.0f * y * y);

	return Matrix3d<T>(
		x00, x01, x02,
		x10, x11, x12,
		x20, x21, x22
		);
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *(this);
}

template<typename T>
T Quaternion<T>::getNorm() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
}

template<typename T>
Quaternion<T>& Quaternion<T>::normalize()
{
	const T norm = getNorm();
	x /= norm;
	y /= norm;
	z /= norm;
	z /= norm;
	assert(isNormalized());
	return *this;
}

template<typename T>
bool Quaternion<T>::isNormalized() const
{
	return Tolerance<T>::isEqualStrictly(getNorm(), 1.0);
}

/*
template<typename T>
void Quaternion<T>::getMult(const Quaternion& q1, const Quaternion& q2)
{
	const auto pw = q1.getW();
	const auto px = q1.getX();
	const auto py = q1.getY();
	const auto pz = q1.getZ();

	const auto qw = q2.getW();
	const auto qx = q2.getX();
	const auto qy = q2.getY();
	const auto qz = q2.getZ();

	this->w = pw * qw - px * qx - py * qy - pz * qz;
	this->x = pw * qx + px * qw + py * qz - pz * qy;
	this->y = pw * qy - px * qz + py * qw + pz * qx;
	this->z = pw * qz + px * qy - py * qx + pz * qw;
}
*/

template<typename T>
Quaternion<T> Quaternion<T>::mult(const Quaternion<T>& rhs) const
{
	const auto pw = this->getW();
	const auto px = this->getX();
	const auto py = this->getY();
	const auto pz = this->getZ();

	const auto qw = rhs.getW();
	const auto qx = rhs.getX();
	const auto qy = rhs.getY();
	const auto qz = rhs.getZ();

	const auto w = pw * qw - px * qx - py * qy - pz * qz;
	const auto x = pw * qx + px * qw + py * qz - pz * qy;
	const auto y = pw * qy - px * qz + py * qw + pz * qx;
	const auto z = pw * qz + px * qy - py * qx + pz * qw;
	return Quaternion<T>(x, y, z, w);
}


template<typename T>
Quaternion<T> Quaternion<T>::getConjugate() const
{
	return Quaternion<T>(-x, -y, -z, w);
}

template<typename T>
bool Quaternion<T>::equals(const Quaternion<T>& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(this->x, rhs.x) &&
		Tolerance<T>::isEqualLoosely(this->y, rhs.y) &&
		Tolerance<T>::isEqualLoosely(this->z, rhs.z) &&
		::fabs(this->w - rhs.w) < 1.0e-6;
//		Tolerance<T>::isEqualLoosely(this->w, rhs.w);
}

template<typename T>
bool Quaternion<T>::operator==(const Quaternion<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Quaternion<T>::operator!=(const Quaternion<T>& rhs) const
{
	return !equals(rhs);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*=(const T s)
{
	this->x *= x;
	this->y *= y;
	this->z *= z;
	this->w *= s;
	return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& s)
{
	*this = mult(s);
	return *this;
}


template<typename T>
Quaternion<T> Quaternion<T>::operator/=(const T s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::getInverse() const
{
	const auto norm = getNorm();
	auto conjugete = getConjugate();
	conjugete /= (norm*norm);
	return conjugete;
}


template class Quaternion<float>;
template class Quaternion<double>;