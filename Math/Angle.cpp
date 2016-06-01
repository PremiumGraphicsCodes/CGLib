#include "Angle.h"

#include "Tolerance.h"

#include <cassert>

using namespace Crystal::Math;

template<typename T>
Degree<T>::Degree() :
	deg(0)
{}

template<typename T>
Degree<T>::Degree(const T deg):
	deg(deg)
{
	assert(T{ 0 } <= deg && deg <= T{ 360 });
}

template<typename T>
Radian<T> Degree<T>::toRadian() const
{
	return Radian<T>(deg / T{ 180 } *Tolerance<T>::getPI());
}

template<typename T>
bool Degree<T>::equals(const Degree<T> rhs) const
{
	return Tolerance<T>::isEqualLoosely(deg, rhs.deg);
}

template<typename T>
bool Degree<T>::operator==(const Degree<T> rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Degree<T>::operator!=(const Degree<T> rhs) const
{
	return !equals(rhs);
}


template<typename T>
Radian<T>::Radian() :
	rad(0)
{
}

template<typename T>
Radian<T>::Radian(const T rad) :
	rad(rad)
{
	assert(T{ 0 } <= rad && rad <= T{ 2 } *Tolerance<T>::getPI());
}

template<typename T>
Degree<T> Radian<T>::toDegree() const
{
	return Degree<T>(rad * T{ 180 } / Tolerance<T>::getPI());
}

template<typename T>
bool Radian<T>::equals(const Radian<T> rhs) const
{
	return Tolerance<T>::isEqualLoosely(rad, rhs.rad);
}

template<typename T>
bool Radian<T>::operator==(const Radian<T> rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Radian<T>::operator!=(const Radian<T> rhs) const
{
	return !equals(rhs);
}


template<typename T>
Angle<T>::Angle()
{}

template<typename T>
Angle<T>::Angle(const Degree<T> deg) :
	deg(deg)
{
}

template<typename T>
Angle<T>::Angle(const Radian<T> rad) :
	deg(rad.toDegree())
{}

template<typename T>
bool Angle<T>::equals(const Degree<T> rhs) const
{
	return deg.equals(rhs);
}

template<typename T>
bool Angle<T>::operator==(const Degree<T> rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Angle<T>::operator!=(const Degree<T> rhs) const
{
	return !equals(rhs);
}

template<typename T>
T Angle<T>::getPI()
{
	return Tolerance<T>::getPI();
}

template<typename T>
T Angle<T>::getX() const
{
	return ::cos(deg.get());
}

template<typename T>
T Angle<T>::getY() const
{
	return ::sin(deg.get());
}



template class Degree<float>;
template class Degree<double>;

template class Radian<float>;
template class Radian<double>;

template class Angle<float>;
template class Angle<double>;