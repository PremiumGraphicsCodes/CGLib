#ifndef __CRYSTAL_MATH_SPACE_H__
#define __CRYSTAL_MATH_SPACE_H__

#include "Vector3d.h"
#include <array>
#include "Index3d.h"

namespace Crystal {
	namespace Math {

template< typename T >
class Space3d final
{
public:
	Space3d() = default;

	explicit Space3d(const Vector3d<T>& origin);

	Space3d(const Vector3d<T>& origin, const Vector3d<T>& length);

	~Space3d() = default;

	//static Space3d<T> FromTwoPoint(const Vector3d<T>& start)

	static Space3d<T> Unit() { return Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)); }

	bool isInner(const Math::Vector3d<float>& position) const;

	bool isOuter(const Math::Vector3d<float>& position) const;

	Vector3d<T> getStart() const { return origin; }

	Vector3d<T> getLengths() const { return vector; }

	T getVolume() const;

	Vector3d<T> getEnd() const { return origin + vector; }

	Vector3d<T> getCenter() const { return origin + vector * 0.5; }

	void scale(const Vector3d<T>& v) { vector.scale( v.getX(), v.getY(), v.getZ() ); }

	Space3d moveStart(const Vector3d<T>& v) const;

	void moveStart(const Vector3d<T>& v);

	Space3d<T> moveEnd(const Vector3d<T>& v) const;

	void moveEnd(const Vector3d<T>& v);

	void move(const Vector3d<T>& v);

	bool equals(const Space3d& rhs) const;

	bool operator==(const Space3d& rhs) const { return equals(rhs); }

	bool operator!=(const Space3d& rhs) const { return !equals(rhs); }

	Space3d<T> getSubSpace(const Index3d index, const unsigned int xdiv, const unsigned int ydiv, const unsigned int zdiv) const;

	std::vector< Space3d<T> > getSubSpaces(const int xdiv, const int ydiv, const int zdiv) const;

	std::vector< Space3d<T> > getDividedWithEdge(const int xdiv, const int ydiv, const int zdiv) const;

	std::array< Vector3d<T>, 8 > toArray() const;

	bool hasIntersection(const Space3d& rhs) const;

	Space3d getOverlapped(const Space3d& rhs) const;

	Space3d<T> offset(const Vector3d<T>& v) const;

	Space3d<T> getBoundingSpace(const Space3d<T>& rhs) const;

	Vector3d<T> getMin() const;

	Vector3d<T> getMax() const;

	Space3d<T> createPowerOfTwoSpace() const;

	Vector3d<T> getPowerOfTwo() const;

private:
	Vector3d<T> origin;
	Vector3d<T> vector;
};


	}
}

#endif