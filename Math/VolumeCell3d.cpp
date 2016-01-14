#include "VolumeCell3d.h"

#include "PositionValue.h"


using namespace Crystal::Math;

template< typename GeomType, typename ValueType >
std::array< PositionValue<GeomType, ValueType>, 8 > VolumeCell3d<GeomType,ValueType>::toPositionValues() const
{
	std::array< PositionValue<GeomType, ValueType>, 8 > pvs;
	const auto& positions = space.toArray();
	for (size_t i = 0; i < 8; ++i) {
		pvs[i] = PositionValue<GeomType, ValueType>(positions[i], values[i]);
	}
	return pvs;
}

template class VolumeCell3d<float, float>;
template class VolumeCell3d<float, double>;
//template class VolumeCell3d<double, float>;
template class VolumeCell3d<double, double>;
