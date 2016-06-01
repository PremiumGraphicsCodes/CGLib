#include "Radian.h"
#include "Degree.h"
#include <cassert>
#include "Tolerance.h"

using namespace Crystal::Math;

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

template class Radian<float>;
template class Radian<double>;