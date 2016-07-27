#include "Vector2d.h"

using namespace Crystal::Math;

template<typename T>
Vector2d<T>::Vector2d()
	: Vector2d(0, 0)
{}

template<typename T>
Vector2d<T>::Vector2d(const T x, const T y) :
	x(x), y(y)
{}

template<typename T>
void Vector2d<T>::scale(const T scale)
{
	x *= scale;
	y *= scale;
}


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
bool Vector2d<T>::equals(const Vector2d& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(this->x, rhs.x) &&
		Tolerance<T>::isEqualLoosely(this->y, rhs.y);
}

template<typename T>
Angle<T> Vector2d<T>::getAngle(const Vector2d<T>& rhs) const
{
	return Angle<T>(Radian<T>( std::acos(getInnerProduct(rhs)) ) );
}

template<typename T>
Angle<T> Vector2d<T>::getSignedAngle(const Vector2d<T>& rhs) const
{
	const auto angle = getAngle(rhs);
	return isLeft(rhs) ? angle : -angle;
}

template<typename T>
T Vector2d<T>::getInnerProduct(const Vector2d<T>& rhs) const
{
	return x*rhs.x + y * rhs.y;
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
Vector2d<T> Vector2d<T>::normalized() const
{
	Vector2d<T> vector = *(this);
	return vector.normalize();
}

template<typename T>
Angle<T> Vector2d<T>::getAngle() const
{
	return Angle<T>(Radian<T>(::atan2(y, x)));
}

template<typename T>
Vector2d<T>& Vector2d<T>::operator+=(const Vector2d& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

template<typename T>
Vector2d<T>& Vector2d<T>::operator-=(const Vector2d& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

#include "Vector3d.h"

template<typename T>
bool Vector2d<T>::isLeft(const Vector2d<T>& rhs) const
{
	const auto v1 = Vector3d<T>(*this);
	const auto v2 = Vector3d<T>(rhs);
	return v1.getOuterProduct(v2).getZ() > 0;
}


template<typename T>
bool Vector2d<T>::isRight(const Vector2d<T>& rhs) const
{
	const auto v1 = Vector3d<T>(*this);
	const auto v2 = Vector3d<T>(rhs);
	return v1.getOuterProduct(v2).getZ() < 0;
}

template class Vector2d<float>;
template class Vector2d<double>;