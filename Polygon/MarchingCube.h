#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_H__


#include "PolygonReduction.h"
#include "../Math/Triangle.h"
#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include "../Math/MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;

		template<typename, typename>
		class VolumeCell3d;
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

		void march(const Math::Volume3d<float, float>& volume, const float isolevel);

		TriangleMesh* getMesh() { return mesh.clone(); }

	private:
		Math::MarchingCubeTable table;
		TriangleMesh mesh;

		void build(const Math::VolumeCell3d<float, float>& cell, const float isolevel);

		void build(const int cubeindex, const std::array<Vertex*, 12>& vertices);

		int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

		std::array< Vertex*, 12 > createVertices(const int cubeindex, const Math::VolumeCell3d<float, float>& cell, const float isolevel);

	};
	}
}

#endif