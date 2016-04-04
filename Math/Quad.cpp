#include "Quad.h"

using namespace Crystal::Math;

template<typename T>
Vector3d<T> Quad<T>::getNormal() const
{
	const auto v1 = positions[1] - positions[0];
	const auto v2 = positions[2] - positions[0];
	return v1.getOuterProduct(v2);
}

/*
template<typename T>
std::vector< Vector3d<T> > Quad<T>::toInnerPoints() const
{
	const auto startx = 
}
*/

template class Quad<float>;