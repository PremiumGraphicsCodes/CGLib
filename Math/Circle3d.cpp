#include "Circle3d.h"

using namespace Crystal::Math;

template<typename T>
Circle3d<T>::Circle3d():
	radius(0.5),
	normal(Vector3d<T>(0,0,1))
{
}

template<typename T>
Circle3d<T>::Circle3d(const T radius,const Vector3d<T>& center, const Vector3d<T>& normal) :
	radius(radius),
	center(center),
	normal(normal)
{
}

template class Circle3d<float>;
template class Circle3d<double>;