#include "Angle.h"

#include "Tolerance.h"

#include <cassert>

using namespace Crystal::Math;

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
bool Angle<T>::equals(const Angle<T> rhs) const
{
	return deg.equals(rhs.deg);
}

template<typename T>
bool Angle<T>::operator==(const Angle<T> rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Angle<T>::operator!=(const Angle<T> rhs) const
{
	return !equals(rhs);
}

template<typename T>
bool Angle<T>::operator<(const Angle<T> rhs) const
{
	return this->deg.get() < rhs.deg.get();
}

template<typename T>
bool Angle<T>::operator>(const Angle<T> rhs) const
{
	return this->deg.get() < rhs.deg.get();
}

template<typename T>
Angle<T> Angle<T>::Zero()
{
	return Angle<T>(Degree<T>(0));
}

template<typename T>
Angle<T> Angle<T>::HalfPI()
{
	return Angle<T>(Degree<T>(90));
}

template<typename T>
Angle<T> Angle<T>::PI()
{
	return Angle<T>(Degree<T>(180));
}

template<typename T>
Angle<T> Angle<T>::DoublePI()
{
	return Angle<T>(Degree<T>(360));

}

/*
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
*/
template<typename T>
T Angle<T>::getSin() const
{
	return ::sin(getRadian().get());
}

template<typename T>
T Angle<T>::getCos() const
{
	return ::cos(getRadian().get());
}

template class Angle<float>;
template class Angle<double>;