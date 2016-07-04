#include "Plane3d.h"
#include "Line3d.h"

using namespace Crystal::Math;

template<typename T>
Plane3d<T>::Plane3d(const Vector3d<T>& center, const Vector3d<T>& basis1, const Vector3d<T>& basis2) :
	IPrimitive3d<T>(center),
	basis1( basis1 ),
	basis2( basis2 )
{
}

template<typename T>
Vector3d<T> Plane3d<T>::getNormal() const
{
	return basis1.getOuterProduct(basis2);
}

template<typename T>
T Plane3d<T>::getDistance(const Vector3d<T>& p) const
{
	return std::fabs(getSignedDistance(p));
}


template<typename T>
T Plane3d<T>::getSignedDistance(const Vector3d<T>& p) const
{
	const auto v = p - center;
	const auto n = getNormal();
	return n.getInnerProduct(v);
}

template<typename T>
bool Plane3d<T>::hasIntersection(const Line3d<T>& line) const
{
	const auto d1 = getSignedDistance( line.getStart() );
	const auto d2 = getSignedDistance(line.getEnd());
	return (d1 * d2) < 0;
}


template<typename T>
Vector3d<T> Plane3d<T>::getIntersection(const Line3d<T>& line) const
{
	assert(hasIntersection(line));
	const auto d1 = getDistance(line.getStart());
	const auto d2 = getDistance(line.getEnd());
	const auto param = d1 / (d1 + d2);
	return line.getPosition(param);
}

template<typename T>
bool Plane3d<T>::equals(const Plane3d<T>& rhs) const
{
	return
		center == rhs.center &&
		orientation == rhs.orientation &&
		basis1 == rhs.basis1 &&
		basis2 == rhs.basis2;
}

template<typename T>
Vector3d<T> Plane3d<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return center + basis1 * u.get() + basis2 * v.get();
}

template<typename T>
Point3d<T> Plane3d<T>::getPoint(const Param<T> u, const Param<T> v) const
{
	const auto pos = getPosition(u, v);
	const auto norm = getNormal();
	const Vector2d<T> param(u.get(), v.get());
	return Point3d<T>(pos, norm, param);
}

template<typename T>
Curve3d<T> Plane3d<T>::toCurve3d() const
{
	Curve3d<T> curve(2,2);
	curve.set(0, 0, getPoint(Param<T>{0}, Param<T>{0}));
	curve.set(0, 1, getPoint(Param<T>{0}, Param<T>{1}));
	curve.set(1, 0, getPoint(Param<T>{1}, Param<T>{0}));
	curve.set(1, 1, getPoint(Param<T>{1}, Param<T>{1}));
	return curve;
}


template class Plane3d<float>;
template class Plane3d<double>;