#include "Plane3d.h"
#include "Line3d.h"

using namespace Crystal::Math;

template<typename T>
Plane3d<T>::Plane3d(const Vector3d<T>& point, const Vector3d<T>& basis1, const Vector3d<T>& basis2) :
	point( point ),
	basis1( basis1.getNormalized() ),
	basis2( basis2.getNormalized() )
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
	const auto v = p - point;
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

template class Plane3d<float>;
template class Plane3d<double>;