#ifndef __CRYSTAL_MATH_POLAR_COORD_3D_H__
#define __CRYSTAL_MATH_POLAR_COORD_3D_H__

#include "Angle.h"
#include "Matrix3d.h"
#include "Quaternion.h"

namespace Crystal {
	namespace Math {

template<typename T>
class PolarCoord3d
{
public:
	PolarCoord3d();

	PolarCoord3d(const T length, const Angle<T> azimuth, const Angle<T> elevation);

	T getLength() const { return length; }

	Angle<T> getTheta() const { return azimuth; }

	Angle<T> getPhi() const { return elevation; }

	Vector3d<T> toOrtho() const;

	Matrix3d<T> toMatrix() const;

	Quaternion<T> getOrientation() const;

	bool equals(const PolarCoord3d<T>& rhs) const;

	bool operator==(const PolarCoord3d<T>& rhs) const;

	bool operator!=(const PolarCoord3d<T>& rhs) const;

	bool isValid() const;


private:
	T length;
	Angle<T> azimuth;
	Angle<T> elevation;
};
	}
}

#endif