#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_H__


#include "Vertex.h"
#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Grid3d.h"
#include "../Math/Triangle.h"
#include "../Util/UnCopyable.h"
#include "VolumeObject.h"
#include "MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;
	}

	namespace Polygon {




class MarchingCube final : UnCopyable
{
public:
	MarchingCube() {
		table.buildEdgeTable();
		table.buildTriangleTable();
	}

	~MarchingCube() = default;

	std::vector< Math::Triangle<float> > march(const Math::Space3d<float>& space, const Math::Grid3d<float>& grid, const float isolevel);
	
	std::vector< Math::Triangle<float> > march(const VolumeObject& volume, const float isolevel);

private:
	MarchingCubeTable table;

	int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

	std::array< Math::Vector3d<float>, 12 > getPositions(const int cubeindex, const VolumeCell& cell, const float isolevel) const;

};

	}
}

#endif