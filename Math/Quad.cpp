#include "Quad.h"

using namespace Crystal::Math;

template<typename T>
Quad<T> Quad<T>::XYPlane(const Vector3d<T>& origin)
{
	return Quad<T>(origin, Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
}

template<typename T>
Quad<T> Quad<T>::YZPlane(const Vector3d<T>& origin)
{
	return Quad<T>(origin, Vector3d<T>(0, 1, 0), Vector3d<T>(0, 0, 1));
}

template<typename T>
Quad<T> Quad<T>::ZXPlane(const Vector3d<T>& origin)
{
	return Quad<T>(origin, Vector3d<T>(0, 0, 1), Vector3d<T>(1, 0, 0));
}

template<typename T>
Vector3d<T> Quad<T>::getNormal() const
{
	const auto v1 = uVector.getNormalized();
	const auto v2 = vVector.getNormalized();
	return v1.getOuterProduct(v2);
}

/*
template<typename T>
std::vector< Vector3d<T> > Quad<T>::toInnerPoints() const
{
	const auto startx = 
}
*/

template<typename T>
Vector3d<T> Quad<T>::getPosition(const T u, const T v) const
{
	return origin + (uVector * u) + (vVector * v);	
}


template<typename T>
std::array<Vector3d<T>, 4> Quad<T>::getPositions() const
{
	const auto v1 = getPosition(0, 0);
	const auto v2 = getPosition(0, 1);
	const auto v3 = getPosition(1, 0);
	const auto v4 = getPosition(1, 1);
	return{ v1,v2,v3,v4 };
}

template<typename T>
bool Quad<T>::equals(const Quad<T>& rhs) const
{
	return origin == rhs.origin &&
		uVector == rhs.uVector &&
		vVector == rhs.vVector;
}

template<typename T>
bool Quad<T>::operator==(const Quad<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Quad<T>::operator!=(const Quad<T>& rhs) const
{
	return !equals(rhs);
}



template class Quad<float>;
template class Quad<double>;