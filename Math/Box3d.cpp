#include "Box3d.h"
#include "Space3d.h"

using namespace Crystal::Math;

template<typename T>
Box3d<T>::Box3d()
	: Box3d(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1))
{
}

template<typename T>
Box3d<T>::Box3d(const Vector3d<T>& point) :
	start(point),
	end(point)
{
}


template<typename T>
Box3d<T>::Box3d(const Vector3d<T>& pointX, const Vector3d<T>& pointY)
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
void Box3d<T>::add(const Vector3d<T>& v) {
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
T Box3d<T>::getVolume() const
{
	return (end.getX() - getMinX()) * (end.getY() - getMinY()) * (end.getZ() - getMinZ());
}

template<typename T>
bool Box3d<T>::isInterior(const Vector3d<T>& point) const
{
	const bool xIsInterior = (getMinX() < point.getX() && point.getX() < end.getX());
	const bool yIsInterior = (getMinY() < point.getY() && point.getY() < end.getY());
	const bool zIsInterior = (getMinZ() < point.getZ() && point.getZ() < end.getZ());
	return xIsInterior && yIsInterior && zIsInterior;
}

template<typename T>
bool Box3d<T>::isExterior(const Vector3d<T>& point) const
{
	return !isInterior(point);
}


template<typename T>
void Box3d<T>::add(const Box3d<T>& b)
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
Vector3d<T> Box3d<T>::getCenter() const
{
	return Vector3d<T>(
		(getMinX() + end.getX()) / T{ 2 },
		(getMinY() + end.getY()) / T{ 2 },
		(getMinZ() + end.getZ()) / T{ 2 }
	);
}

template<typename T>
Box3d<T> Box3d<T>::getOverlapped(const Box3d<T>& rhs) const
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
	return Box3d(min_, max_);
}

template<typename T>
bool Box3d<T>::equals(const Box3d<T>& rhs) const
{
	return
		start == rhs.getStart() &&
		Tolerance<T>::isEqualLoosely(end.getX(), rhs.end.getX()) &&
		Tolerance<T>::isEqualLoosely(end.getY(), rhs.end.getY()) &&
		Tolerance<T>::isEqualLoosely(end.getZ(), rhs.end.getZ());
}

template<typename T>
bool Box3d<T>::hasIntersection(const Box3d& rhs) const
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
void Box3d<T>::outerOffset(const T offsetLength)
{
	const auto x = getMinX() - offsetLength;
	const auto y = getMinY() - offsetLength;
	const auto z = getMinZ() - offsetLength;
	start = Vector3d<T>(x, y, z);
	end += Vector3d<T>(offsetLength, offsetLength, offsetLength);
	assert(isValid());
}

template<typename T>
std::vector<Vector3d<T>> Box3d<T>::toPoints(const T divideLength) const
{
	std::vector<Vector3d<T>> points;
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
bool Box3d<T>::isValid() const
{
	return
		(getMinX() <= end.getX()) && (getMinY() <= end.getY()) && (getMinZ() <= end.getZ());
}


template<typename T>
bool Box3d<T>::isShirinked() const
{
	return
		(getMinX() == end.getX()) && (getMinY() == end.getY()) && (getMinZ() == end.getZ());
}

template<typename T>
Space3d<T> Box3d<T>::toSpace() const
{
	return Space3d<T>(start, getLength());
}

template<typename T>
std::vector<Vector3d<T>> Box3d<T>::toSurfacePositions(const T divideLength) const
{
	std::vector<Vector3d<T>> results;
	const auto minx = getMinX() + divideLength * T{ 0.5 };
	const auto maxx = getMaxX() - divideLength * T{ 0.5 };
	const auto miny = getMinY() + divideLength * T{ 0.5 };
	const auto maxy = getMaxY() - divideLength * T{ 0.5 };
	const auto minz = getMinZ() + divideLength * T{ 0.5 };
	const auto maxz = getMaxZ() - divideLength * T{ 0.5 };
	for (auto x = minx; x <= maxx; x += divideLength) {
		for (auto y = miny; y <= maxy; y += divideLength) {
			results.push_back( Vector3d<T>(x, y, minz) );
			results.push_back( Vector3d<T>(x, y, maxz) );
		}
	}
	for (auto y = miny; y <= maxy; y += divideLength) {
		for (auto z = minz; z <= maxz; z += divideLength) {
			results.push_back(Vector3d<T>(minx, y, z));
			results.push_back(Vector3d<T>(maxx, y, z));
		}
	}
	for (auto z = minz; z <= maxz; z += divideLength) {
		for (auto x = minz; x <= maxz; x += divideLength) {
			results.push_back(Vector3d<T>(x, minz, z));
			results.push_back(Vector3d<T>(x, maxz, z));
		}
	}
	return results;
}

#include "Quad3d.h"

template<typename T>
Quad3d<T> Box3d<T>::getXMinusQuad() const
{
	return Quad3d<T>::YZPlane(getMin());
}

template<typename T>
Quad3d<T> Box3d<T>::getXPlusQuad() const
{
	const auto& origin = getPosition(Vector3d<T>(1, 0, 0));
	const auto& dir1 = getPosition(Vector3d<T>(1, 0, 1));
	const auto& dir2 = getPosition(Vector3d<T>(1, 1, 0));
	return Quad3d<T>(origin, dir1, dir2);
}

template<typename T>
Quad3d<T> Box3d<T>::getYMinusQuad() const
{
	return Quad3d<T>::ZXPlane(getMin());
}

template<typename T>
Quad3d<T> Box3d<T>::getYPlusQuad() const
{
	return Quad3d<T>::ZXPlane(Vector3d<T>(getMinX(), getMaxY(), getMinZ()));
}
/*

template<typename T>
Quad<T> Box3d<T>::getZMinusQuad() const
{

}

template<typename T>
Quad<T> Box3d<T>::getZPlusQuad() const
{

}
*/

#include "Curve3d.h"

template<typename T>
Curve3d<T> Box3d<T>::toCurve3d() const
{
	/*
	getXMinusQuad().toCurve2d();
	getXPlusQuad().toCurve2d();
	*/
	Curve3d<T> curve(2,2);
	//curve.set
	return curve;
}

template<typename T>
Vector3d<T> Box3d<T>::getPosition(const Vector3d<T>& param) const
{
	const auto& length = getLength();
	const auto x = start.getX() + length.getX() * param.getX();
	const auto y = start.getY() + length.getY() * param.getY();
	const auto z = start.getZ() + length.getZ() * param.getZ();
	return Vector3d<T>(x, y, z);
}


template class Box3d<float>;
template class Box3d<double>;