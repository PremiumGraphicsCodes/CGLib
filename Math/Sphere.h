#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Vector3d.h"

#include "Box.h"

#include <vector>
#include <cassert>
#include <algorithm>

namespace Crystal {
	namespace Math {

template<typename T>
class Sphere final
{
public:
	Sphere() :
		center( Vector3d<T>::Zero() ),
		radius( 1.0f )
	{}

	Sphere( const Vector3d<T>& center, const float radius ) :
		center( center ),
		radius( radius )
	{}

	Sphere( const Math::Box<T>& boundingBox ) {
		center = Vector3d<T>( boundingBox.getCenter().getX(), boundingBox.getCenter().getY(), boundingBox.getCenter().getZ() );
		const Vector3d<T>& length = boundingBox.getLength();
		radius = std::min<float>( std::min<float>( length.getX(), length.getY() ), length.getZ() ) * 0.5f;
	}

	static Sphere UnitSphere() {
		return Sphere( Vector3d<float>::Zero(), 1.0f );
	}

	Math::Box<T> getBoundingBox() const {
		Math::Box<T> box( center, center );
		return box.getOuterOffset( radius );
	}

	Vector3dVector<T> toPoints(const float divideLength ) const {
		Vector3dVector<T> points;

		Math::Box box( center, center );
		box.outerOffset( radius );

		for( float x = box.getMinX(); x <= box.getMaxX(); x+= divideLength ) {
			for( float y = box.getMinY(); y <= box.getMaxY(); y += divideLength ) {
				for( float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength ) {
					const Vector3d pos( x, y, z );
					if( pos.getDistanceSquared( center ) < radius * radius ) {
						points.push_back( pos );
					}
				}
			}
		}
		return points;
	}


	Vector3d<T> getCenter() const { return center; }

	float getRadius() const { return radius; }

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

	bool isOuter(const Vector3d<float>& v) const {
		return v.getDistanceSquared(center) > (radius * radius);
	}

	bool isInner(const Vector3d<float>& v) const {
		return !isOuter(v);
	}

	bool isOnStrictly(const Vector3d<float>& v) const {
		return Tolerance<T>::isEqualStrictly(v.getDistanceSquared(center), radius * radius);
	}

	bool isOnLoosely(const Vector3d<float>& v) const {
		return Tolerance<T>::isEqualLoosely(v.getDistanceSquared(center), radius * radius);
	}

private:
	Vector3d<T> center;
	T radius;
};

	}
}

#endif