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

		class MCEdge;

class MCCell {
public:
	MCCell() {
	}

	MCCell(const Math::Vector3d<float>& position, float value):
		position( position),
		value(value)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	float getValue() const { return value; }


	std::array< Vertex*, 12 > vertices;

private:
	Math::Vector3d<float> position;
	float value;
};



class MCGrid
{
public:
	MCGrid(const Math::Volume3d<float,float>& volume, const float threshold);

	float getValue(int x, int y, int z) const {
		return grid[x][y][z].getValue();
	}

	bool isUnderThreshold(int x, int y, int z) const {
		return getValue(x, y, z) < threshold;
	}

	std::bitset<8> getBit(int x, int y, int z) const;

	void createEdges();

	std::vector< Vertex* > getVertices() const { return mesh.getVertices(); }

	Math::Vector3d<float> getPosition(const MCCell& v1, const MCCell& v2)
	{
		const float scale = (threshold - v1.getValue()) / (v2.getValue() - v1.getValue());
		return v1.getPosition() + scale * (v2.getPosition() - v1.getPosition());
	}


private:

	std::vector< std::vector< std::vector< MCCell > > > grid;
	const int sizeX;
	const int sizeY;
	const int sizeZ;
	const float threshold;
	MarchingCubeTable table;

	TriangleMesh mesh;
};

	}
}

#endif