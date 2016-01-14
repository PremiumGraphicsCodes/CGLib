#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector3d.h"
#include <array>
#include "Index3d.h"

namespace Crystal {
	namespace Math {



template< typename T >
class Space3d final {
public:
	Space3d() = default;

	explicit Space3d(const Vector3d<T>& origin);

	Space3d(const Vector3d<T>& origin, const Vector3d<T>& length);

	~Space3d() = default;

	static Space3d<T> Unit() { return Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)); }

	Vector3d<T> getStart() const { return origin; }

	Vector3d<T> getLengths() const { return vector; }

	T getVolume() const { return vector.getX() * vector.getY() * vector.getZ(); }

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { return origin + vector * 0.5; }

	void scale(const Vector3d<T>& v) { vector.scale( v.getX(), v.getY(), v.getZ() ); }

	Space3d moveStart(const Vector3d<T>& v) const { return Space3d<T>(origin + v, vector - v); }

	void moveStart(const Vector3d<T>& v) {
		origin += v;
		vector -= v;
	}

	Space3d<T> moveEnd(const Vector3d<T>& v) const { return Space3d<T>(origin, vector + v); }

	void moveEnd(const Vector3d<T>& v) { vector += v; }

	Space3d& move(const Vector3d<T>& v) {
		moveStart(v);
		moveEnd(v);
		return (*this);
	}

	bool equals(const Space3d& rhs) const;

	bool operator==(const Space3d& rhs) const { return equals(rhs); }

	bool operator!=(const Space3d& rhs) const { return !equals(rhs); }

	Space3d<T> getSubSpace(const Index3d index, const unsigned int xdiv, const unsigned int ydiv, const unsigned int zdiv) const;

	std::vector< Space3d<T> > getSubSpaces(const int xdiv, const int ydiv, const int zdiv) const;

	std::vector< Space3d<T> > getDividedWithEdge(const int xdiv, const int ydiv, const int zdiv) const;

	std::array< Vector3d<T>, 8 > toArray() const;

	bool hasIntersection(const Space3d& rhs) const;

	Space3d getOverlapped(const Space3d& rhs) const;

	Space3d<T> offset(const Vector3d<T>& v) const { return Space3d<T>(origin + v * 0.5, vector - v); }

	Space3d<T> getBoundingSpace(const Space3d<T>& rhs) const;

private:
	Vector3d<T> origin;
	Vector3d<T> vector;
};


	}
}

#endif