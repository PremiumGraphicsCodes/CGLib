#ifndef __CRYSTAL_MATH_POSITION_VALUE_H__
#define __CRYSTAL_MATH_POSITION_VALUE_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename GeomType, typename ValueType>
class PositionValue
{
public:
	PositionValue();

	PositionValue(const Vector3d<GeomType>& p, const ValueType& v);

	Vector3d<GeomType> getInterpolatedPosition(const ValueType v, const PositionValue& rhs) const;

	bool equals(const PositionValue& rhs) const;

	bool operator==(const PositionValue& rhs) const { return equals(rhs); }

	bool operator!=(const PositionValue& rhs) const { return !equals(rhs); }

private:
	Math::Vector3d<GeomType> pos;
	ValueType value;
};

	}
}

#endif