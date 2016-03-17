#include "Box.h"
#include "Space3d.h"

using namespace Crystal::Math;

template<typename T>
Box<T>::Box()
	: Box(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1))
{
}

template<typename T>
Box<T>::Box(const Vector3d<T>& point) :
	start(point),
	end(point)
{
}


template<typename T>
Box<T>::Box(const Vector3d<T>& pointX, const Vector3d<T>& pointY)
{
	const auto x = std::min<T>(pointX.getX(), pointY.getX());
	const auto y = std::min<T>(pointX.getY(), pointY.getY());
	const auto z = std::min<T>(pointX.getZ(), pointY.getZ());
	this->start = Vector3d<T>(x, y, z);
	const auto endX = std::max<T>(pointX.getX(), pointY.getX());
	const auto endY = std::max<T>(pointX.getY(), pointY.getY());
	const auto endZ = std::max<T>(pointX.getZ(), pointY.getZ());
	this->end = Vector3d<T>(endX, endY, endZ);
	assert(isValid());
}


template<typename T>
void Box<T>::add(const Vector3d<T>& v) {
	const auto x = std::min<T>(getMinX(), v.getX());
	const auto y = std::min<T>(getMinY(), v.getY());
	const auto z = std::min<T>(getMinZ(), v.getZ());
	start = Vector3d <T>(x, y, z);

	const auto endX = std::max<T>(end.getX(), v.getX());
	const auto endY = std::max<T>(end.getY(), v.getY());
	const auto endZ = std::max<T>(end.getZ(), v.getZ());
	end = Vector3d<T>(endX, endY, endZ);
}

template<typename T>
T Box<T>::getVolume() const
{
	return (end.getX() - getMinX()) * (end.getY() - getMinY()) * (end.getZ() - getMinZ());
}

template<typename T>
bool Box<T>::isInterior(const Vector3d<T>& point) const
{
	const bool xIsInterior = (getMinX() < point.getX() && point.getX() < end.getX());
	const bool yIsInterior = (getMinY() < point.getY() && point.getY() < end.getY());
	const bool zIsInterior = (getMinZ() < point.getZ() && point.getZ() < end.getZ());
	return xIsInterior && yIsInterior && zIsInterior;
}

template<typename T>
bool Box<T>::isExterior(const Vector3d<T>& point) const
{
	return !isInterior(point);
}


template<typename T>
void Box<T>::add(const Box<T>& b)
{
	const auto sx = std::min<T>(getMinX(), b.getMinX());
	const auto sy = std::min<T>(getMinY(), b.getMinY());
	const auto sz = std::min<T>(getMinZ(), b.getMinZ());
	this->start = Vector3d<T>(sx, sy, sz);

	const auto ex = std::max<T>(end.getX(), b.getMaxX());
	const auto ey = std::max<T>(end.getY(), b.getMaxY());
	const auto ez = std::max<T>(end.getZ(), b.getMaxZ());
	this->end = Vector3d<T>(ex, ey, ez);
}

template<typename T>
Vector3d<T> Box<T>::getCenter() const
{
	return Vector3d<T>(
		(getMinX() + end.getX()) / T{ 2 },
		(getMinY() + end.getY()) / T{ 2 },
		(getMinZ() + end.getZ()) / T{ 2 }
	);
}

template<typename T>
Box<T> Box<T>::getOverlapped(const Box<T>& rhs) const
{
	assert(hasIntersection(rhs));
	const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
	const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());
	const auto minz = std::max<T>(this->getStart().getZ(), rhs.getStart().getZ());

	const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
	const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());
	const auto maxz = std::min<T>(this->getEnd().getZ(), rhs.getEnd().getZ());

	const Vector3d<T> min_(minx, miny, minz);
	const Vector3d<T> max_(maxx, maxy, maxz);
	return Box(min_, max_);
}

template<typename T>
bool Box<T>::equals(const Box<T>& rhs) const
{
	return
		start == rhs.getStart() &&
		Tolerance<T>::isEqualLoosely(end.getX(), rhs.end.getX()) &&
		Tolerance<T>::isEqualLoosely(end.getY(), rhs.end.getY()) &&
		Tolerance<T>::isEqualLoosely(end.getZ(), rhs.end.getZ());
}

template<typename T>
bool Box<T>::hasIntersection(const Box& rhs) const
{
	const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
	const auto lx = getLength().getX() / T{ 2 } +rhs.getLength().getX() / T{ 2 };

	const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
	const auto ly = getLength().getY() / T{ 2 } +rhs.getLength().getY() / T{ 2 };

	const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
	const auto lz = getLength().getZ() / T{ 2 } +rhs.getLength().getZ() / T{ 2 };

	return (distx < lx && disty < ly && distz < lz);
}

template<typename T>
void Box<T>::outerOffset(const T offsetLength)
{
	const auto x = getMinX() - offsetLength;
	const auto y = getMinY() - offsetLength;
	const auto z = getMinZ() - offsetLength;
	start = Vector3d<T>(x, y, z);
	end += Vector3d<T>(offsetLength, offsetLength, offsetLength);
	assert(isValid());
}

template<typename T>
Vector3dVector<T> Box<T>::toPoints(const T divideLength) const
{
	Vector3dVector<T> points;
	for (T x = getMinX(); x <= end.getX(); x += divideLength) {
		for (T y = getMinY(); y <= end.getY(); y += divideLength) {
			for (T z = getMinZ(); z <= end.getZ(); z += divideLength) {
				points.push_back(Vector3d<T>(x, y, z));
			}
		}
	}
	return points;
}

template<typename T>
bool Box<T>::isValid() const
{
	return
		(getMinX() <= end.getX()) && (getMinY() <= end.getY()) && (getMinZ() <= end.getZ());
}


template<typename T>
bool Box<T>::isShirinked() const
{
	return
		(getMinX() == end.getX()) && (getMinY() == end.getY()) && (getMinZ() == end.getZ());
}

template<typename T>
Space3d<T> Box<T>::toSpace() const
{
	return Space3d<T>(start, getLength());
}


template class Box<float>;
template class Box<double>;