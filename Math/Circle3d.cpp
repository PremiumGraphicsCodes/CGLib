#include "Circle3d.h"

using namespace Crystal::Math;

template<typename T>
Circle3d<T>::Circle3d():
	radius(0.5),
	normal(Vector3d<float>(0,0,1))
{
}

template<typename T>
Circle3d<T>::Circle3d(const Vector3d<T>& center, const Vector3d<T>& normal) :
	center(center),
	normal(normal)
{
}