#include "AngleParam.h"
#include "Param.h"

#include <cassert>

using namespace Crystal::Math;

template<typename T>
AngleParam<T>::AngleParam() :
	param(0)
{}

template<typename T>
AngleParam<T>::AngleParam(T param)
{
	assert(isValid());
}

template<typename T>
Param<T> AngleParam<T>::toParam() const
{
	return Param<T>( param / T{ 360 } );
}

template<typename T>
bool AngleParam<T>::isValid() const
{
	return (T{ 0 } <= param && param <= T{ 360 });
}


template class AngleParam<float>;
template class AngleParam<double>;
