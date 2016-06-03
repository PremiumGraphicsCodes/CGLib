#ifndef __CRYSTAL_MATH_POLAR_COORD_3D_H__
#define __CRYSTAL_MATH_POLAR_COORD_3D_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Matrix3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class PolarCoord3d
{
public:
	PolarCoord3d();

	PolarCoord3d(const T length, const Angle<T> theta, const Angle<T> phi);

	explicit PolarCoord3d(const Vector3d<T>& v);

	T getLength() const { return length; }

	Angle<T> getTheta() const { return theta; }

	Angle<T> getPhi() const { return phi; }

	Vector3d<T> toOrtho() const;

	Matrix3d<T> toMatrix() const;

	bool equals(const PolarCoord3d<T>& rhs) const;

	bool operator==(const PolarCoord3d<T>& rhs) const;

	bool operator!=(const PolarCoord3d<T>& rhs) const;


private:
	T length;
	Angle<T> theta;
	Angle<T> phi;
};
	}
}

#endif