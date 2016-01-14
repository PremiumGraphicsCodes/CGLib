#ifndef __CRYSTAL_MATH_VOLUME_3D_H__
#define __CRYSTAL_MATH_VOLUME_3D_H__

#include "Grid3d.h"
#include "Space3d.h"

namespace Crystal {
	namespace Math {


template< typename, typename>
class VolumeCell3d;

template< typename GeomType, typename ValueType>
class Volume3d
{
public:
	Volume3d();

	Volume3d(const Space3d<GeomType>& space_, const Grid3d<ValueType>& grid);

	std::vector<ValueType> getValues() const;

	Grid3d<ValueType> getGrid() const { return grid; }

	Space3d<GeomType> getSpace() const { return space; }

	VolumeCell3d<GeomType, ValueType> toCell(const Index3d index) const;

	std::vector< VolumeCell3d<GeomType, ValueType> > toCells() const;

	std::vector< VolumeCell3d<GeomType, ValueType> > toBoundaryCells(const ValueType threshold) const;

	std::vector< VolumeCell3d<GeomType, ValueType> > toBoundaryCellsWithEdge(const ValueType threshold) const;

	bool equals(const Volume3d<GeomType, ValueType>& rhs) const;

	bool operator==(const Volume3d<GeomType, ValueType>& rhs) const { return equals(rhs); }

	bool operator!=(const Volume3d<GeomType, ValueType>& rhs) const { return !equals(rhs); }

	Vector3d<GeomType> getStart() const { return space.getStart(); }

	Vector3d<GeomType> getCenter() const { return space.getCenter(); }

	Vector3d<GeomType> getEnd() const { return space.getEnd(); }

	Vector3d<GeomType> getUnitLengths() const;

	Vector3d<GeomType> toCenterPosition(const size_t x, const size_t y, const size_t z) const;

	Vector3dVector<GeomType> toCenterPositions() const;

private:
	Grid3d<ValueType> grid;
	Space3d<GeomType> space;
};

	}
}

#endif