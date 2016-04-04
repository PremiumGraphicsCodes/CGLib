#ifndef __CRYSTAL_MATH_BOX_3D_H__
#define __CRYSTAL_MATH_BOX_3D_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Math{
		template<typename>
		class Space3d;
template<typename T>
class Box3d final
{
public:
	
	Box3d();

	Box3d(const Vector3d<T>& point);

	Box3d(const Vector3d<T>& pointX, const Vector3d<T>& pointY);

	~Box3d() = default;

	static Box3d Unit() {
		return Box3d();
	}

	Box3d getBoundingBox() const { return *this; }

	void add(const Vector3d<T>& v);

	void add(const Box3d& b);

	T getVolume() const;

	Vector3d<T> getMax() const { return Vector3d<T>(end.getX(), end.getY(), end.getZ()); }
	
	Vector3d<T> getMin() const { return Vector3d<T>(getMinX(), getMinY(), getMinZ()); }

	Vector3d<T> getStart() const { return getMin(); }

	Vector3d<T> getEnd() const { return getMax(); }

	Vector3d<T> getCenter() const;

	bool isInterior(const Vector3d<T>& point) const;

	bool isExterior(const Vector3d<T>& point) const;

	void outerOffset(const T offsetLength);

	Box3d getOuterOffset(const T offsetLength) const {
		Box3d box = *this;
		box.outerOffset(offsetLength);
		return box;
	}

	void innerOffset(const T offsetLength) {
		outerOffset(-offsetLength);
		assert(isValid());
	}

	Box3d getInnerOffset(const T offsetLength) const {
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

	bool equals(const Box3d& rhs) const;

	bool operator==( const Box3d& rhs ) const { return equals( rhs ); }

	bool operator!=( const Box3d& rhs ) const { return !equals( rhs ); }

	bool hasIntersection(const Box3d& rhs) const;

	Box3d getOverlapped(const Box3d& rhs) const;

	Space3d<T> toSpace() const;

	std::vector<Math::Vector3d<T>> toSurfacePositions(const T divideLength) const;

private:
	Vector3d<T> start;
	Vector3d<T> end;
};

	}
}

#endif