#include "Space2d.h"

using namespace Crystal::Math;

template class Space2d<float>;
template class Space2d<double>;

template<typename T>
bool Space2d<T>::isIn(const Vector2d<T>& point) const
{
	const bool xIsIn = (origin.getX() <= point.getX()) && (point.getX() <= origin.getX() + vector.getX());
	const bool yIsIn = (origin.getY() <= point.getY()) && (point.getY() <= origin.getY() + vector.getY());
	return xIsIn && yIsIn;
}

template<typename T>
bool Space2d<T>::equals(const Space2d<T>& rhs) const
{
	return
		getStart() == rhs.getStart() &&
		getLengths() == rhs.getLengths();
}
