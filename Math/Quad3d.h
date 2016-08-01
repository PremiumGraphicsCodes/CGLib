#ifndef __CRYSTAL_MATH_QUAD_3D_H__
#define __CRYSTAL_MATH_QUAD_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Point3d;
		template<typename T>
		class Curve3d;
		template<typename T>
		class Polyline3d;

template<typename T>
class Quad3d
{
public:
	Quad3d(const Vector3d<T>& origin, const Vector3d<T>& uVector, const Vector3d<T>& vVector) :
		origin(origin),
		uVector(uVector),
		vVector(vVector)
	{}

	static Quad3d<T> XYPlane(const Vector3d<T>& origin);

	static Quad3d<T> YZPlane(const Vector3d<T>& origin);

	static Quad3d<T> ZXPlane(const Vector3d<T>& origin);

	Math::Vector3d<T> getNormal() const;

	Vector3d<T> getPosition(const T u, const T v) const;

	Point3d<T> getPoint(const T u, const T v) const;

	std::array<Vector3d<T>, 4> getPositions() const;

	bool equals(const Quad3d<T>& rhs) const;

	bool operator==(const Quad3d<T>& rhs) const;

	bool operator!=(const Quad3d<T>& rhs) const;

	//Point2d toPoint(const T u, const T v) const;

	Curve3d<T> toCurve3d() const;

	Polyline3d<T> toPolyline() const;

private:
	Vector3d<T> origin;
	Vector3d<T> uVector;
	Vector3d<T> vVector;
};
	}
}

#endif