#ifndef __CRYSTAL_MATH_ELLIPSE_3D_H__
#define __CRYSTAL_MATH_ELLIPSE_3D_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Param.h"
#include "Quaternion.h"
#include "IPrimitive3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Curve3d;
		template<typename>
		class Polyline3d;

template<typename T>
class Ellipse3d : public IPrimitive3d<T>
{
public:
	Ellipse3d();

	Ellipse3d(const Vector3d<T> radii, const Vector3d<T>& center, const Quaternion<T>& orientation);

	bool equals(const Ellipse3d<T>& rhs) const;

	bool operator==(const Ellipse3d<T>& rhs) const;

	bool operator!=(const Ellipse3d<T>& rhs) const;

	Vector3d<T> getPosition(const Angle<T> angle) const;

	Vector3d<T> getPosition(const Param<T> param) const;

	Polyline3d<T> toPolyline(const int number) const;

	//Curve3d<T> toCurve3d() const;

private:
	Vector3d<T> radii;
};

	}
}

#endif