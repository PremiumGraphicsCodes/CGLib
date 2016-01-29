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
	MCNode() :
		xplus(nullptr),
		xminus(nullptr),
		yplus(nullptr),
		yminus(nullptr),
		zplus(nullptr),
		zminus(nullptr)
	{}

	MCNode(const Math::Vector3d<float>& position, const float value) :
		position(position),
		value(value),
		xminus(nullptr),
		yplus(nullptr),
		yminus(nullptr),
		zplus(nullptr),
		zminus(nullptr)

	{}

	Math::Vector3d<float> getPosition() { return position; }

	float getValue() const { return value; }

	bool isUnderThreshold(float threshold) const { return this->value < threshold; }

	MCNode* xplus;
	MCNode* xminus;
	MCNode* yplus;
	MCNode* yminus;
	MCNode* zplus;
	MCNode* zminus;


private:
	Math::Vector3d<float> position;
	float value;

};

class MCEdge
{
public:
	MCEdge() :
		node1(nullptr),
		node2(nullptr)
	{}

	MCEdge(MCNode* node1, MCNode* node2):
		node1(node1),
		node2(node2)
	{}

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

	MCCell(const std::array< MCNode*, 8 >& nodes, const std::array< MCEdge*, 12 >& edges) :
		nodes(nodes),
		edges( edges )
	{
	}


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

private:
	std::array< MCNode*, 8 > nodes;
	std::array< MCEdge*, 12 > edges;
};



class MCGrid
{
public:
	MCGrid(const Math::Volume3d<float, float>& volume, const float threshold);

	~MCGrid();

	std::bitset<8> getBit(int x, int y, int z) const;

	std::vector< Vertex* > getVertices() const { return mesh.getVertices(); }


private:
	std::vector< std::vector< std::vector< MCNode* > > > nodes;
	std::vector< MCEdge* > edges;
	std::vector< MCCell* > cells;

	const float threshold;
	MarchingCubeTable table;

	TriangleMesh mesh;
};

	}
}

#endif