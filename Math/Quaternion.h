#ifndef __CRYSTAL_MATH_QUATERNION_H__
#define __CRYSTAL_MATH_QUATERNION_H__

#include "Vector3d.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Math{

template<typename T>
class Quaternion
{
public:	
	Quaternion(void);

	Quaternion(const T x, const T y, const T z, const T w);

	Quaternion(const Vector3d<T>& axis, const T angle);

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

	void getMult(const Quaternion& q1, const Quaternion& q2) {
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

private:
	T x;
	T y;
	T z;
	T w;
};

	}
}

#endif