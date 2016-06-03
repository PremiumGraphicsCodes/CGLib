#ifndef __CRYSTAL_MATH_QUATERNION_H__
#define __CRYSTAL_MATH_QUATERNION_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Math{

template<typename>
class Matrix3d;

template<typename T>
class Quaternion
{
public:	
	Quaternion(void);

	Quaternion(const T x, const T y, const T z, const T w);

	Quaternion(const Vector3d<T>& axis, const T angle);

	static Quaternion Unit() { return Quaternion(0, 0, 0, 1); }

	Matrix3d<T> toMatrix() const;

	Quaternion& operator+=(const Quaternion& rhs);

	T getNorm() const;

	Quaternion& normalize();

	bool isNormalized() const;

	T getX() const { return x; }

	T getY() const { return y; }

	T getZ() const { return z; }

	T getW() const { return w; }

	void setX( const T x ) { this->x = x; }

	void setY( const T y ) { this->y = y; }

	void setZ( const T z ) { this->z = z; }

	void setW( const T w ) { this->w = w; }

	//void getMult(const Quaternion& q1, const Quaternion& q2);

	Quaternion<T> mult(const Quaternion<T>& rhs) const;

	Quaternion<T> getConjugate() const;

	Quaternion<T> getInverse() const;

	bool equals(const Quaternion<T>& rhs) const;

	bool operator==(const Quaternion<T>& rhs) const;

	bool operator!=(const Quaternion<T>& rhs) const;

	Quaternion<T> operator*=(const T s);

	Quaternion<T> operator*(const Quaternion<T>& s);

	Quaternion<T>& operator*=(const Quaternion<T>& s);

	Quaternion<T> operator/=(const T s);


private:
	T x;
	T y;
	T z;
	T w;
};

	}
}

#endif