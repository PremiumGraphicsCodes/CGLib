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

template<typename T>
bool Point2d<T>::equals(const Point2d<T>& rhs) const
{
	return
		position == rhs.position &&
		normal == rhs.normal &&
		Tolerance<T>::isEqualLoosely(parameter, rhs.parameter);
}

template<typename T>
bool Point2d<T>::operator==(const Point2d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Point2d<T>::operator!=(const Point2d<T>& rhs) const
{
	return !equals(rhs);
}


template class Point2d<float>;
template class Point2d<double>;