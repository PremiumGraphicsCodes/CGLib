#ifndef __CRYSTAL_GRAPHICS_MARCHING_CUBE_H__
#define __CRYSTAL_GRAPHICS_MARCHING_CUBE_H__


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

	namespace Graphics {
		namespace Experiment {

	class MarchingCube final : UnCopyable
	{
	public:
		MarchingCube() {
			table.buildEdgeTable();
			table.buildTriangleTable();
		}

		static MarchingCube* getInstance() {
			static MarchingCube instance;
			return &instance;
		}

		~MarchingCube() = default;

		void march(const Math::Volume3d<float, float>& ss, const float isolevel) const;

		TriangleMesh getMesh() const { return mesh; }

	private:
		Math::MarchingCubeTable table;
		TriangleMesh mesh;

		void build(const Math::VolumeCell3d<float, float>& cell, const float isolevel) const;

		void build(const int cubeindex, const std::array<Math::Vector3d<float>, 12>& vertices) const;

		int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

		std::array< Math::Vector3d<float>, 12 > getPositions(const int cubeindex, const Math::VolumeCell3d<float, float>& cell, const float isolevel) const;

	};
		}
	}
}

#endif