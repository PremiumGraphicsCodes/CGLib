#include "Cylinder.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cylinder<T>::Cylinder() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cylinder<T>::Cylinder(const T radius, const T height) :
	radius(radius),
	height(height)
{
}

template<typename T>
T Cylinder<T>::getVolume() const
{
	return radius * radius * Tolerance<T>::getPI() * height;
}

/*
template<typename T>
T Cylinder<T>::getRadius() const
{

}
*/

template class Cylinder<float>;
template class Cylinder<double>;