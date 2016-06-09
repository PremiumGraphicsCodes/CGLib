#include "Point2d.h"

using namespace Crystal::Math;

template<typename T>
Point2d<T>::Point2d(const Vector2d<T>& position) :
	position(position)
{}

template<typename T>
Point2d<T>::Point2d(const Vector2d<T>& position, const Vector2d<T>& normal) :
	position(position),
	normal(normal)
{
}

template<typename T>
Point2d<T>::Point2d(const Vector2d<T>& position, const Vector2d<T>& normal, const T parameter) :
	position(position),
	normal(normal),
	parameter(parameter)
{
}

template class Point2d<float>;
template class Point2d<double>;