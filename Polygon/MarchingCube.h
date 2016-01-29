#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_H__


#include "Vertex.h"
#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Volume3d.h"
#include "../Util/UnCopyable.h"
#include "../Math/MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;
	}

	namespace Polygon {

		class MCEdge;

class MarchingCube final : UnCopyable
{
public:
	MarchingCube() {
		table.buildEdgeTable();
		table.buildTriangleTable();
	}

	~MarchingCube() = default;

	void march(const Math::Volume3d<float, float>& ss, const float isolevel);

	//TriangleMesh* cloneMesh() {mesh->}
	TriangleMesh* cloneMesh() { return mesh.clone(); }

	std::list< Vertex* > getVertices() { return mesh.getVertices(); }

private:
	Math::MarchingCubeTable table;
	TriangleMesh mesh;

	int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

	std::array< Math::Vector3d<float>, 12 > getPositions(const int cubeindex, const Math::VolumeCell3d<float, float>& cell, const float isolevel) const;

};

	}
}

#endif