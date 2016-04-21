#include "Box2d.h"
//#include "Space3d.h"
#include <cassert>
#include <algorithm>

using namespace Crystal::Math;

template<typename T>
Box2d<T>::Box2d()
	: Box2d<T>(Vector2d<T>(0, 0), Vector2d<T>(1, 1))
{
}

template<typename T>
Box2d<T>::Box2d(const Vector2d<T>& pointX, const Vector2d<T>& pointY)
{
	const auto x = std::min<T>(pointX.getX(), pointY.getX());
	const auto y = std::min<T>(pointX.getY(), pointY.getY());
	this->start = Vector2d<T>(x, y);
	const auto endX = std::max<T>(pointX.getX(), pointY.getX());
	const auto endY = std::max<T>(pointX.getY(), pointY.getY());
	this->end = Vector2d<T>(endX, endY);
	assert(isValid());
}

template<typename T>
void Box2d<T>::add(const Vector2d<T>& v) {
	const auto x = std::min<T>(getMinX(), v.getX());
	const auto y = std::min<T>(getMinY(), v.getY());
	start = Vector2d<T>(x, y);

	const auto endX = std::max<T>(end.getX(), v.getX());
	const auto endY = std::max<T>(end.getY(), v.getY());
	end = Vector2d<T>(endX, endY);
}

template<typename T>
T Box2d<T>::getArea() const
{
	return (end.getX() - getMinX()) * (end.getY() - getMinY());
}

/*
template<typename T>
bool Box2d<T>::isInterior(const Vector2d<T>& point) const
{
	const bool xIsInterior = (getMinX() < point.getX() && point.getX() < end.getX());
	const bool yIsInterior = (getMinY() < point.getY() && point.getY() < end.getY());
	return xIsInterior && yIsInterior;
}

template<typename T>
bool Box2d<T>::isExterior(const Vector2d<T>& point) const
{
	return !isInterior(point);
}
*/
template<typename T>
void Box2d<T>::add(const Box2d<T>& b)
{
	const auto sx = std::min<T>(getMinX(), b.getMinX());
	const auto sy = std::min<T>(getMinY(), b.getMinY());
	this->start = Vector2d<T>(sx, sy);

	const auto ex = std::max<T>(end.getX(), b.getMaxX());
	const auto ey = std::max<T>(end.getY(), b.getMaxY());
	this->end = Vector2d<T>(ex, ey);
}

template<typename T>
Vector2d<T> Box2d<T>::getCenter() const
{
	return Vector2d<T>(
		(getMinX() + end.getX()) / T{ 2 },
		(getMinY() + end.getY()) / T{ 2 }
	);
}

template<typename T>
Box2d<T> Box2d<T>::getOverlapped(const Box2d<T>& rhs) const
{
	assert(hasIntersection(rhs));
	const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
	const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());

	const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
	const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());

	const Vector2d<T> min_(minx, miny);
	const Vector2d<T> max_(maxx, maxy);
	return Box2d(min_, max_);
}

template<typename T>
bool Box2d<T>::equals(const Box2d<T>& rhs) const
{
	return
		start == rhs.getStart() &&
		Tolerance<T>::isEqualLoosely(end.getX(), rhs.end.getX()) &&
		Tolerance<T>::isEqualLoosely(end.getY(), rhs.end.getY());
}

template<typename T>
bool Box2d<T>::hasIntersection(const Box2d& rhs) const
{
	const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
	const auto lx = getLength().getX() / T{ 2 } +rhs.getLength().getX() / T{ 2 };

	const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
	const auto ly = getLength().getY() / T{ 2 } +rhs.getLength().getY() / T{ 2 };

	return (distx < lx && disty < ly);
}

/*
template<typename T>
void Box2d<T>::outerOffset(const T offsetLength)
{
	const auto x = getMinX() - offsetLength;
	const auto y = getMinY() - offsetLength;
	const auto z = getMinZ() - offsetLength;
	start = Vector3d<T>(x, y, z);
	end += Vector3d<T>(offsetLength, offsetLength, offsetLength);
	assert(isValid());
}

template<typename T>
std::vector< Vector2d<T> > Box2d<T>::toPoints(const T divideLength) const
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
*/
template<typename T>
bool Box2d<T>::isValid() const
{
	return
		(getMinX() <= end.getX()) && (getMinY() <= end.getY());
}

template<typename T>
bool Box2d<T>::isShirinked() const
{
	return
		(getMinX() == end.getX()) && (getMinY() == end.getY());
}

/*
template<typename T>
Space3d<T> Box2d<T>::toSpace() const
{
	return Space3d<T>(start, getLength());
}
*/

template<typename T>
std::array< T, 8 > Box2d<T>::toArray() const
{
	return{
		getMinX(), getMaxY(),
		getMinX(), getMinY(),
		getMaxX(), getMinY(),
		getMaxX(), getMaxY()
	};
}


template class Box2d<float>;
template class Box2d<double>;