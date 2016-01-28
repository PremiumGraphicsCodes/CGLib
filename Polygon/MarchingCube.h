#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_H__


#include "Vertex.h"
#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Volume3d.h"
#include "../Util/UnCopyable.h"
#include "MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;
	}

	namespace Polygon {

	class MCCube {
	public:
		MCCube(const std::array< float, 8 >& val, const float isolevel);

	public:
		std::bitset<8> getBit() const { return bit; }

	private:
		std::bitset<8> bit;

	};

	class MCVertex {
	public:
		MCVertex() {
		}

		MCVertex(const Math::Vector3d<float>& position, float value):
			position( position),
			value(value)
		{}

		Math::Vector3d<float> position;
		float value;
	};

	class MCEdge
	{
	public:
		MCEdge()
		{}

		MCEdge(const MCVertex& v1, const MCVertex& v2) :
			v1(v1),
			v2(v2)
		{}

		Math::Vector3d<float> getInterpolatedPosition(const float value) const
		{
			const float scale = (value - v1.value) / (v2.value - v1.value);
			return v1.position + scale * (v2.position - v1.position);
		}


		MCVertex v1;
		MCVertex v2;
	};

	class MCCell
	{
	public:
		MCCell(const Math::Space3d<float>& space, const std::array< float, 8>& values) :
			space(space),
			values(values)
		{}

		Math::Space3d<float> getSpace() const { return space; }

		std::array< float , 8 > getValues() const { return values; }

		std::array< MCVertex, 8 > toPositionValues() const {
			std::array< MCVertex, 8 > pvs;
			const auto& positions = space.toArray();
			for (size_t i = 0; i < 8; ++i) {
				pvs[i] = MCVertex(positions[i], values[i]);
			}
			return pvs;
		}

	private:
		Math::Space3d<float> space;
		std::array< float, 8> values;
	};



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
		MarchingCubeTable table;
		TriangleMesh mesh;

		void build(const MCCell& cell, const float isolevel);

		std::vector< Vertex* > createVertices(const int cubeindex, const MCCell& cell, const float isolevel);

	};
	}
}

#endif