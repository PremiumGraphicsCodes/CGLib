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
	assert(T{ 0 } <= deg && T{ 360 } <= deg);
}

template<typename T>
Radian<T> Degree<T>::toRadian() const
{
	return Radian<T>(deg / T{ 180 } *Tolerance<T>::getPI());
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
	assert(T{ 0 } <= rad && (T{ 2 } *Tolerance<T>::getPI()) <= rad);

}

template<typename T>
Degree<T> Radian<T>::toDegree() const
{
	return Degree<T>(rad * T{ 180 } / Tolerance<T>::getPI());
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

template class Degree<float>;
template class Degree<double>;

template class Radian<float>;
template class Radian<double>;

template class Angle<float>;
template class Angle<double>;