#ifndef __CRYSTAL_MATH_BOX_H__
#define __CRYSTAL_MATH_BOX_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Math{

template<typename T>
class Box final
{
public:
	
	Box();

	Box(const Vector3d<T>& pointX, const Vector3d<T>& pointY);

	~Box() = default;

	static Box Unit() {
		return Box();
	}

	Box getBoundingBox() const { return *this; }

	void add(const Vector3d<T>& v);

	void add(const Box& b);

	T getVolume() const;

	Vector3d<T> getMax() const { return Vector3d<T>(end.getX(), end.getY(), end.getZ()); }
	
	Vector3d<T> getMin() const { return Vector3d<T>(getMinX(), getMinY(), getMinZ()); }

	Vector3d<T> getStart() const { return getMin(); }

	Vector3d<T> getEnd() const { return getMax(); }

	Vector3d<T> getCenter() const;

	bool isInterior(const Vector3d<T>& point) const;

	bool isExterior(const Vector3d<T>& point) const;

	void outerOffset(const T offsetLength);

	Box getOuterOffset(const T offsetLength) const {
		Box box = *this;
		box.outerOffset(offsetLength);
		return box;
	}

	void innerOffset(const T offsetLength) {
		outerOffset(-offsetLength);
		assert(isValid());
	}

	Box getInnerOffset(const T offsetLength) const {
		return getOuterOffset(-offsetLength);
	}

	Vector3dVector<T> toPoints(const T divideLength) const;

	T getMaxX() const { return end.getX(); }

	T getMinX() const { return start.getX(); }

	T getMaxY() const { return end.getY(); }

	T getMinY() const { return start.getY(); }

	T getMaxZ() const { return end.getZ(); }

	T getMinZ() const { return start.getZ(); }

	Vector3d<T> getLength() const {
		return Vector3d<T>(end.getX() - getMinX(), end.getY() - getMinY(), end.getZ() - getMinZ());
	}

	bool isValid() const;

	bool isShirinked() const;

	bool equals(const Box& rhs) const;

	bool operator==( const Box& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box& rhs ) const { return !equals( rhs ); }

	bool hasIntersection(const Box& rhs) const;

	Box getOverlapped(const Box& rhs) const;

private:
	Vector3d<T> start;
	Vector3d<T> end;
};

	}
}

#endif