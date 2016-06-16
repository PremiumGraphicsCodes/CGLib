#include "Vector2d.h"

using namespace Crystal::Math;

//template<typename T>
//Vector2d<T>::isIn(const Vector2d<T>& )

template<typename T>
T Vector2d<T>::getDistanceSquared(const Vector2d& rhs) const
{
	return pow(x - rhs.x, 2) + pow(y - rhs.y, 2);
}

template<typename T>
T Vector2d<T>::getLengthSquared() const
{
	return x*x + y*y;
}

template<typename T>
T Vector2d<T>::getLength() const
{
	return std::sqrt(getLengthSquared());
}


template<typename T>
Vector2d<T> Vector2d<T>::normalize()
{
	const auto length = getLength();
	x /= length;
	y /= length;
	return *this;
}

template<typename T>
Vector2d<T> Vector2d<T>::getNormalized() const
{
	Vector2d<T> vector = *(this);
	return vector.normalize();
}

template<typename T>
Angle<T> Vector2d<T>::getAngle() const
{
	return Angle<T>(Radian<T>(::atan2(y, x)));
}

template class Vector2d<float>;
template class Vector2d<double>;