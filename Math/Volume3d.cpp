#include "Volume3d.h"

using namespace Crystal::Math;

template<typename GeomType, typename ValueType>
Volume3d<GeomType,ValueType>::Volume3d() :
	Volume3d(Space3d<GeomType>::Unit(), Grid3d<ValueType>(2, 2, 2))
{}

template<typename GeomType, typename ValueType>
Volume3d<GeomType, ValueType>::Volume3d(const Space3d<GeomType>& space_, const Grid3d<ValueType>& grid) :
	space(space_),
	grid(grid)
{
}

template<typename GeomType, typename ValueType>
std::vector<ValueType> Volume3d<GeomType, ValueType>::getValues() const
{
	std::vector<ValueType> values;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				values.push_back(grid.get(x, y, z));
			}
		}
	}
	return values;
}



template<typename GeomType, typename ValueType>
Vector3d<GeomType> Volume3d<GeomType, ValueType>::toCenterPosition(const size_t x, const size_t y, const size_t z) const
{
	const auto unitLengths = getUnitLengths();
	const auto xx = x * unitLengths.getX() + unitLengths.getX() * GeomType(0.5) + getStart().getX();
	const auto yy = y * unitLengths.getY() + unitLengths.getY() * GeomType(0.5) + getStart().getY();
	const auto zz = z * unitLengths.getZ() + unitLengths.getZ() * GeomType(0.5) + getStart().getZ();
	return Vector3d<GeomType>(xx, yy, zz);
}

template<typename GeomType, typename ValueType>
Vector3dVector<GeomType> Volume3d<GeomType, ValueType>::toCenterPositions() const
{
	Vector3dVector<GeomType> positions;
	for (auto x = 0; x < grid.getSizes()[0]; ++x) {
		for (auto y = 0; y < grid.getSizes()[1]; ++y) {
			for (auto z = 0; z < grid.getSizes()[2]; ++z) {
				positions.push_back(toCenterPosition(x, y, z));
			}
		}
	}
	return positions;
}




template<typename GeomType, typename ValueType>
bool Volume3d<GeomType, ValueType>::equals(const Volume3d<GeomType, ValueType>& rhs) const
{
	return
		this->grid == rhs.grid &&
		this->getSpace() == rhs.getSpace();
}


template<typename GeomType, typename ValueType>
Vector3d<GeomType> Volume3d<GeomType,ValueType>::getUnitLengths() const
{
	const auto x = space.getLengths().getX() / grid.getSizes()[0];
	const auto y = space.getLengths().getY() / grid.getSizes()[1];
	const auto z = space.getLengths().getZ() / grid.getSizes()[2];
	return Vector3d<GeomType>(x, y, z);
}


template class Volume3d<float, float>;
template class Volume3d<float, double>;
template class Volume3d<double, double>;