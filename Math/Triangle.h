#ifndef __CRYSTAL_MATH_TRIANGLE_H__
#define __CRYSTAL_MATH_TRIANGLE_H__

#include <vector>
#include <cassert>

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Triangle final
{
public:
	Triangle() :
		v0(Vector3d<T>(0.0, 0.0, 0.0)),
		v1(Vector3d<T>(1.0, 0.0, 0.0)),
		v2(Vector3d<T>(0.0, 1.0, 0.0))
	{}

	Triangle( const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) :
		v0( v0 ),
		v1( v1 ),
		v2( v2 )
	{
	}

	static Triangle<T> UnitXY() {
		return Triangle<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(1.0, 0.0, 0.0),
			Vector3d<T>(0.0, 1.0, 0.0)
		);
	}

	static Triangle<T> UnitXZ() {
		return Triangle<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(0.0, 0.0, 1.0),
			Vector3d<T>(1.0, 0.0, 0.0)
			);
	}

	static Triangle<T> UnitYZ() {
		return Triangle<T>(
			Vector3d<T>(0.0, 0.0, 0.0),
			Vector3d<T>(0.0, 1.0, 0.0),
			Vector3d<T>(0.0, 0.0, 1.0)
			);
	}


	Vector3d<T> getNormal() const {
		const Vector3d<T> v01 = v0 - v1;
		const Vector3d<T> v02 = v1 - v2;
		return v01.getOuterProduct(v02).getNormalized();
	}

	T getArea() const {
		const Vector3d<T> v01 = v0 - v1;
		const Vector3d<T> v02 = v1 - v2;
		return v01.getOuterProduct(v02).getLength() * T(0.5);
	}

	bool isCCW() const {
		assert( isValid() );
		return getNormal().getLength() >= 0.0f;
	}

	bool isCW() const {
		assert( isValid() );
		return !isCCW();
	}

	Vector3d<T> getCenter() const {
		return (v0 + v1 + v2) / T(3);
	}

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