#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Vector3d.h"


#include <vector>
#include <cassert>
#include <algorithm>

namespace Crystal {
	namespace Math {
		template<typename T>
		class Box;

template<typename T>
class Sphere final
{
public:
	Sphere();

	Sphere(const Vector3d<T>& center, const float radius);

	Sphere(const Math::Box<T>& boundingBox);

	static Sphere UnitSphere() {
		return Sphere( Vector3d<T>::Zero(), 1.0f );
	}

	Math::Box<T> getBoundingBox() const;

	Vector3dVector<T> toPoints(const float divideLength) const;

	Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	virtual bool isValid() const {
		return radius >= 0.0f;
	}

	void outerOffset(const float offsetLength) {
		this->radius += offsetLength;
		assert( isValid() );
	}

	Sphere getOuterOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius += offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}

	virtual void innerOffset(const float offsetLength) {
		this->radius -= offsetLength;
		assert( isValid() );
	}

	Sphere getInnerOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius -= offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}

	bool equals( const Sphere& rhs ) const {
		return
			Tolerance<T>::isEqualLoosely( radius, rhs.radius) &&
			( center == rhs.center );
	}

	bool operator==( const Sphere& rhs ) const {
		return equals( rhs );
	}

	bool isOuter(const Vector3d<T>& v) const {
		return v.getDistanceSquared(center) > (radius * radius);
	}

	bool isInner(const Vector3d<T>& v) const {
		return v.getDistanceSquared(center) < (radius * radius);
	}

	bool isOnStrictly(const Vector3d<T>& v) const {
		return Tolerance<T>::isEqualStrictly(v.getDistanceSquared(center), radius * radius);
	}

	bool isOnLoosely(const Vector3d<T>& v) const {
		return Tolerance<T>::isEqualLoosely(v.getDistanceSquared(center), radius * radius);
	}

private:
	Vector3d<T> center;
	T radius;
};

	}
}

#endif