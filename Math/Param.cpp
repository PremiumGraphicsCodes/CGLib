#include "Param.h"
#include "Angle.h"

#include <cassert>

using namespace Crystal::Math;

template<typename T>
Param<T>::Param() :
	param(0)
{
	assert(isValid());
}

template<typename T>
Param<T>::Param(T param) :
	param(param)
{
	assert(isValid());
}

template<typename T>
bool Param<T>::isValid() const
{
	return T{ 0 } <= param && param <= T{ 1 };
}

template<typename T>
Angle<T> Param<T>::toAngle() const
{
	return Angle<T>( Degree<T>(param * T{ 360 }));
}
/*
template<typename T>
AngleParam<T> Param<T>::toAngle() const
{

}

template<typename T>
AngleParam<T>::AngleParam() :
	param(0)
{}

template<typename T>
AngleParam<T>::AngleParam(T param)
{

}

Param<T> toParam() const;
*/

template class Param<float>;
template class Param<double>;