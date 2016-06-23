#ifndef __CRYSTAL_MATH_I_PRIMITIVE_3D_H__
#define __CRYSTAL_MATH_I_PRIMITIVE_3D_H__

#include "Vector3d.h"
#include "Quaternion.h"

namespace Crystal {
	namespace Math {

template<typename T>
class IPrimitive3d
{
public:
	IPrimitive3d() = default;

	IPrimitive3d(const Math::Vector3d<T>& center) :
		center(center)
	{
	}

	IPrimitive3d(const Math::Vector3d<T>& center, const Quaternion<T>& orientation) :
		center(center),
		orientation(orientation)
	{
	}


	virtual ~IPrimitive3d() = default;

	Vector3d<T> getCenter() const { return center; }

	void move(const Vector3d<T> v) { this->center += v; }

	void rotate(const Quaternion<T> q) { this->orientation *= q; }

protected:
	Math::Vector3d<T> center;
	Math::Quaternion<T> orientation;
};

	}
}

#endif