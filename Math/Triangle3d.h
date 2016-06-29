#ifndef __CRYSTAL_MATH_TRIANGLE_3D_H__
#define __CRYSTAL_MATH_TRIANGLE_3D_H__

#include <vector>
#include <cassert>

#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Line3d;

template<typename T>
class Triangle3d
{
public:
	Triangle3d();

	Triangle3d(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2);

	static Triangle3d<T> UnitXY() {
		return Triangle3d<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(1.0, 0.0, 0.0),
			Vector3d<T>(0.0, 1.0, 0.0)
		);
	}

	static Triangle3d<T> UnitXZ() {
		return Triangle3d<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(0.0, 0.0, 1.0),
			Vector3d<T>(1.0, 0.0, 0.0)
			);
	}

	static Triangle3d<T> UnitYZ() {
		return Triangle3d<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(0.0, 1.0, 0.0),
			Vector3d<T>(0.0, 0.0, 1.0)
			);
	}


	Vector3d<T> getNormal() const;

	T getArea() const;

	bool isCCW() const;

	bool isCW() const;

	Vector3d<T> getCenter() const;

	bool isValid() const {
		return ( v0 != v1 ) && ( v1 != v2 ) && ( v0 != v2 );
	}

	/*
	bool isShrinekd() const {
		return Tolerance<T>::isEqualLoosely( get)
	}
	*/

	Vector3d<T> getv0() const { return v0; }

	Vector3d<T> getv1() const { return v1; }

	Vector3d<T> getv2() const { return v2; }

	void setv0( const Vector3d<T>& v ) { this->v0 = v; }

	void setv1( const Vector3d<T>& v ) { this->v1 = v; }

	void setv2( const Vector3d<T>& v ) { this->v2 = v; }

	bool equals(const Triangle3d<T>& rhs) const;

	bool operator==(const Triangle3d<T>& rhs) const;

	bool operator!=(const Triangle3d<T>& rhs) const;

	//Vector3d<T> getIntersection(const Line3d<T>& line) const;


private:
	Vector3d<T> v0;
	Vector3d<T> v1;
	Vector3d<T> v2;

};

//template<typename T>
//using TriangleVector = std::vector< Triangle<T> >;

	}
}

#endif