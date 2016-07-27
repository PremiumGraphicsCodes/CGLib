#include "Quad2d.h"

using namespace Crystal::Math;

template<typename T>
Quad2d<T>::Quad2d() :
	origin(Vector2d<T>(0,0)),
	length(Vector2d<T>(1,1))
{}


template<typename T>
Quad2d<T>::Quad2d(const Vector2d<T>& origin, const Vector2d<T>& length) :
	origin(origin),
	length(length)
{}

template<typename T>
void Quad2d<T>::moveStartTo(const Vector2d<T>& start)
{
	length = getEnd() - start;
	this->origin = start;
}

template<typename T>
void Quad2d<T>::moveEndTo(const Vector2d<T>& end)
{
	length = end - getStart();
}

template<typename T>
Vector2d<T> Quad2d<T>::getStart() const
{
	return origin;
}

template<typename T>
Vector2d<T> Quad2d<T>::getEnd() const
{
	return origin + length;
}

template<typename T>
T Quad2d<T>::getArea() const
{
	return length.getX() * length.getY();
}

template<typename T>
bool Quad2d<T>::equals(const Quad2d<T>& rhs) const
{
	return
		origin == rhs.origin &&
		length == rhs.length;
}

template<typename T>
bool Quad2d<T>::operator==(const Quad2d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Quad2d<T>::operator!=(const Quad2d<T>& rhs) const
{
	return !equals(rhs);
}

template class Quad2d<float>;
template class Quad2d<double>;