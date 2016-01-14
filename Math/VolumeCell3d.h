#ifndef __CRYSTAL_MATH_VOLUME_CELL_3D_H__
#define __CRYSTAL_MATH_VOLUME_CELL_3D_H__

#include "Space3d.h"
#include <array>

namespace Crystal {
	namespace Math {

template<typename,typename>
class PositionValue;

template< typename GeomType, typename ValueType >
class VolumeCell3d
{
public:
	VolumeCell3d(const Space3d<GeomType>& space, const std::array< ValueType, 8>& values) :
		space(space),
		values(values)
	{}

	Space3d<GeomType> getSpace() const { return space; }

	std::array< ValueType, 8 > getValues() const { return values; }

	std::array< PositionValue<GeomType, ValueType>, 8 > toPositionValues() const;

private:
	Space3d<GeomType> space;
	std::array< ValueType, 8> values;
};

	}
}

#endif