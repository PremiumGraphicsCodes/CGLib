#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Curve3d.h"

#include <vector>
#include <cassert>
#include <algorithm>

namespace Crystal {
	namespace Math {
		template<typename>
		class Box3d;
		template<typename>
		class Ellipsoid;

template<typename T>
class Sphere final
{
public:
	Sphere();

	Sphere(const Vector3d<T>& center, const float radius);

	Sphere(const Math::Box3d<T>& boundingBox);

	static Sphere UnitSphere();

	Math::Box3d<T> getBoundingBox() const;

	std::vector<Vector3d<T>> toPoints(const T divideLength) const;

	Vector3d<T> getPosition(const Angle<T> u, const Angle<T> v) const;

	Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	bool isValid() const {
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

	void innerOffset(const float offsetLength) {
		this->radius -= offsetLength;
		assert( isValid() );
	}

	Sphere getInnerOffset(const float offsetLength) const;

	bool equals(const Sphere& rhs) const;

	bool operator==(const Sphere& rhs) const;

	bool operator!=(const Sphere& rhs) const;

	bool isInner(const Vector3d<T>& v) const;

	bool isOuter(const Vector3d<T>& v) const;

	bool isOnStrictly(const Vector3d<T>& v) const;

	bool isOnLoosely(const Vector3d<T>& v) const;

	Ellipsoid<T> toEllipsoid() const;

	Curve3d<T> toCurve3d(const int uNum, const int vNum) const;

private:
	Vector3d<T> center;
	T radius;
};

	}
}

#endif