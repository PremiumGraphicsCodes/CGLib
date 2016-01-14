#include "Plane3d.h"

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
T Plane3d<T>::getSignedDistance(const Vector3d<T>& p) const
{
	const auto v = p - point;
	const auto n = getNormal();
	return n.getInnerProduct(v);
}


template class Plane3d<float>;
template class Plane3d<double>;