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

class MCCell {
public:
	MCCell() {
	}

	MCCell(const Math::Vector3d<float>& position, float value):
		position( position),
		value(value)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	float getValue() const { return value; }

private:
	Math::Vector3d<float> position;
	float value;
};

class MCEdge {
public:
	MCEdge(MCCell* cell1, MCCell* cell2) :
		v1(cell1),
		v2(cell2)
	{}

	Math::Vector3d<float> getInterpolatedPosition(const float value) const
	{
		const float scale = (value - v1->getValue()) / (v2->getValue() - v1->getValue());
		return v1->getPosition() + scale * (v2->getPosition() - v1->getPosition());
	}

	MCCell* v1;
	MCCell* v2;
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

	std::bitset<8> getBit(int x, int y, int z) const {
		std::bitset<8> bit;

		const int x1 = x;
		const int y1 = y;
		const int z1 = z;
		const int x2 = x + 1;
		const int y2 = y + 1;
		const int z2 = z + 2;

		if (getValue(x1,y1,z1) < threshold) { bit.set(0); }
		if (getValue(x2,y1,z1) < threshold) { bit.set(1); }
		if (getValue(x2,y2,z1) < threshold) { bit.set(2); }
		if (getValue(x1,y2,z1) < threshold) { bit.set(3); }
		if (getValue(x1,y1,z2) < threshold) { bit.set(4); }
		if (getValue(x2,y1,z2) < threshold) { bit.set(5); }
		if (getValue(x2,y2,z2) < threshold) { bit.set(6); }
		if (getValue(x1,y2,z2) < threshold) { bit.set(7); }
		return bit;
	}

	void createEdges();

	std::vector< Math::Vector3d<float> > createVertices();


private:
	std::vector< std::vector< std::vector< MCCell > > > grid;
	std::vector < std::vector< std::vector< std::list<MCEdge*>> > > gridEdges;
	std::vector<MCEdge> edges;
	const int sizeX;
	const int sizeY;
	const int sizeZ;
	const float threshold;
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


};
	}
}

#endif