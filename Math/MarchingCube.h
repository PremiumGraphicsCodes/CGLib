#ifndef __CRYSTAL_MATH_MARCHING_CUBE_H__
#define __CRYSTAL_MATH_MARCHING_CUBE_H__


#include "Triangle.h"
#include "Vector3d.h"
#include "../Util/UnCopyable.h"
#include "MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {

template<typename,typename>
class Volume3d;

template<typename,typename>
class VolumeCell3d;

template<typename GeomType, typename ValueType>
class MarchingCube final : UnCopyable
{
public:
	MarchingCube() {
		table.buildEdgeTable();
		table.buildTriangleTable();
	}

	static MarchingCube* getInstance() {
		static MarchingCube<GeomType, ValueType> instance;
		return &instance;
	}

	~MarchingCube() = default;

	std::vector< Triangle<GeomType> > march(const Volume3d<GeomType, ValueType>& ss, const ValueType isolevel) const;

private:
	MarchingCubeTable table;

	std::vector< Triangle<GeomType> > build(const VolumeCell3d<GeomType, ValueType>& cell, const ValueType isolevel) const;

	std::vector< Triangle<GeomType> > build(const int cubeindex, const std::array<Vector3d<GeomType>, 12>& vertices) const;

	int getCubeIndex(const std::array< ValueType, 8 >& val, const ValueType isolevel) const;

	std::array< Vector3d<GeomType>, 12 > getPositions(const int cubeindex, const VolumeCell3d<GeomType, ValueType>& cell, const ValueType isolevel) const;

};
	}
}

#endif