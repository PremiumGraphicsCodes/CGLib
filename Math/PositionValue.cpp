#include "PositionValue.h"

using namespace Crystal::Math;

template<typename GeomType, typename ValueType>
PositionValue<GeomType,ValueType>::PositionValue() :
	pos(Vector3d<GeomType>(0, 0, 0)),
	value(0)
{}

template<typename GeomType, typename ValueType>
PositionValue<GeomType, ValueType>::PositionValue(const Vector3d<GeomType>& p, const ValueType& v) :
	pos(p),
	value(v)
{}

template<typename GeomType, typename ValueType>
Vector3d<GeomType> PositionValue<GeomType, ValueType>::getInterpolatedPosition(const ValueType v, const PositionValue& rhs) const
{
	const GeomType scale = (v - this->value) / static_cast<GeomType>(rhs.value - this->value);
	return this->pos + scale * (rhs.pos - this->pos);
}


template<typename GeomType, typename ValueType>
bool PositionValue<GeomType, ValueType>::equals(const PositionValue& rhs) const
{
	return
		pos == rhs.pos &&
		value == rhs.value;
}


//template<typename GeomType, typename ValueType>
template class PositionValue<float, float>;
template class PositionValue<float, double>;
template class PositionValue<double, double>;