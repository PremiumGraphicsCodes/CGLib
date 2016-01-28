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

class MCNode
{
public:
	MCNode()
	{}

	MCNode(const Math::Vector3d<float>& position, const float value) :
		position(position),
		value(value)
	{}

	Math::Vector3d<float> getPosition() { return position; }

	float getValue() const { return value; }

private:
	Math::Vector3d<float> position;
	float value;

};

class MCEdge
{
	Math::Vector3d<float> getPosition(const float threshold)
	{
		const float scale = (threshold - node1->getValue()) / (node2->getValue() - node1->getValue());
		return node1->getPosition() + scale * (node2->getPosition() - node1->getPosition());
	}

	MCNode* node1;
	MCNode* node2;
};

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

	/*
	std::bitset<8> getBit(const float threshold) {
		std::bitset<8> bit;

		if (nodes[0]->getValue() < threshold) { bit.set(0); }
		if (nodes[1]->getValue() < threshold) { bit.set(1); }
		if (getValue(x2, y2, z1) < threshold) { bit.set(2); }
		if (getValue(x1, y2, z1) < threshold) { bit.set(3); }
		if (getValue(x1, y1, z2) < threshold) { bit.set(4); }
		if (getValue(x2, y1, z2) < threshold) { bit.set(5); }
		if (getValue(x2, y2, z2) < threshold) { bit.set(6); }
		if (getValue(x1, y2, z2) < threshold) { bit.set(7); }
		return bit;
	}
	*/

	std::array< Vertex*, 12 > vertices;

private:
	std::array< MCNode*, 8 > nodes;
	std::array< MCEdge*, 12 > edges;
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

	std::vector< MCNode > nodes;

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