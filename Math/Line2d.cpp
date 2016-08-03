#include "Line2d.h"

using namespace Crystal::Math;

template<typename T>
Line2d<T>::Line2d() :
	start(Vector2d<T>(0, 0)),
	vector(Vector2d<T>(0, 0))
{}

template<typename T>
Line2d<T>::Line2d(const Vector2d<T>& start, const Vector2d<T>& end) :
	start(start),
	vector(end - start)
{
}

template<typename T>
void Line2d<T>::moveStartTo(const Vector2d<T>& p)
{
	this->vector += (getStart() - p);
	this->start = p;
}

template<typename T>
bool Line2d<T>::equals(const Line2d<T>& rhs) const
{
	return
		this->start == rhs.start &&
		this->vector == rhs.vector;
}



template class Line2d<float>;
template class Line2d<double>;