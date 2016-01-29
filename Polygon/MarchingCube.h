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
		yplus(nullptr),
		zplus(nullptr)
	{}

	MCNode(const Math::Vector3d<float>& position, const float value) :
		position(position),
		value(value),
		xplus(nullptr),
		yplus(nullptr),
		zplus(nullptr)
	{}

	Math::Vector3d<float> getPosition() { return position; }

	float getValue() const { return value; }

	bool isUnderThreshold(float threshold) const { return this->value < threshold; }

	MCEdge* xplus;
	MCEdge* yplus;
	MCEdge* zplus;


private:
	Math::Vector3d<float> position;
	float value;

};

class MCEdge
{
public:
	MCEdge() :
		startNode(nullptr),
		endNode(nullptr)
	{}

	MCEdge(MCNode* startNode, MCNode* endNode):
		startNode(startNode),
		endNode(endNode)
	{
	}

	Vertex* createVertex(const float threshold)
	{
		const float scale = (threshold - startNode->getValue()) / (endNode->getValue() - startNode->getValue());
		v = new Vertex(startNode->getPosition() + scale * (endNode->getPosition() - startNode->getPosition()));
		return v;
	}


	MCNode* startNode;
	MCNode* endNode;
	Vertex* v;
};


class MCCell {
public:
	MCCell() {
	}

	MCCell(const std::array<MCNode*, 8>& nodes, const std::array<MCEdge*, 12>& edges) :
		nodes( nodes ),
		edges( edges )
	{
	}

	std::bitset<8> getBit(const float threshold) {
		std::bitset<8> bit;

		for (int i = 0; i < 8; ++i){
			if (nodes[i]->isUnderThreshold(threshold)) {
				bit.set(i);
			}
		}
		return bit;
	}

	std::vector<MCEdge*> getActiveEdges() {
		std::vector<MCEdge*> es;
		for (auto e : edges) {
			if (e != nullptr) {
				es.push_back(e);
			}
		}
		return es;
	}


private:
	std::array<MCNode*, 8> nodes;
	std::array<MCEdge*, 12> edges;
};



class MCGrid
{
public:
	MCGrid(const Math::Volume3d<float, float>& volume, const float threshold);

	~MCGrid();

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