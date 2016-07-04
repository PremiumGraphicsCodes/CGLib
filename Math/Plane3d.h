#ifndef __CRYSTAL_MATH_PLANE_3D_H__
#define __CRYSTAL_MATH_PLANE_3D_H__

#include "Vector3d.h"
#include "IPrimitive3d.h"
#include "Param.h"
#include "Curve3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Line3d;

template<typename T>
class Plane3d : public IPrimitive3d<T>
{
public:
	Plane3d(const Math::Vector3d<T>& point, const Math::Vector3d<T>& basis1, const Math::Vector3d<T>& basis2);

	static Plane3d<T> XYPlane() { return Plane3d<T>( Vector3d<T>(0,0,0), Vector3d<T>(1,0,0), Vector3d<T>(0,1,0) ); }

	static Plane3d<T> YZPlane() { return Plane3d<T>( Vector3d<T>(0,0,0), Vector3d<T>(0,1,0), Vector3d<T>(0,0,1) ); }

	static Plane3d<T> ZXPlane() { return Plane3d<T>( Vector3d<T>(0,0,0), Vector3d<T>(0,0,1), Vector3d<T>(1,0,0) ); }

	Math::Vector3d<T> getNormal() const;

	T getDistance(const Math::Vector3d<T>& p) const;

	T getSignedDistance(const Math::Vector3d<T>& p) const;

	bool equals(const Plane3d<T>& rhs) const;

	bool operator==(const Plane3d<T>& rhs) const { return equals(rhs); }

	bool operator!=(const Plane3d<T>& rhs) const { return !equals(rhs); }

	bool hasIntersection(const Line3d<T>& line) const;

	Vector3d<T> getIntersection(const Line3d<T>& line) const;

	Vector3d<T> getPosition(const Param<T> u, const Param<T> v) const;

	Point3d<T> getPoint(const Param<T> u, const Param<T> v) const;

	Curve3d<T> toCurve3d() const;

private:
	const Math::Vector3d<T> basis1;
	const Math::Vector3d<T> basis2;
};
	}
}

#endif