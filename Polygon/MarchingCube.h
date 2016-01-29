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

	Vertex* createVertex(const float threshold, TriangleMesh* mesh)
	{
		const float scale = (threshold - startNode->getValue()) / (endNode->getValue() - startNode->getValue());
		v = mesh->createVertex(startNode->getPosition() + scale * (endNode->getPosition() - startNode->getPosition()));
		return v;
	}

	Vertex* getVertex() const { return v; }

	MCNode* getStartNode() const { return startNode; }

private:
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
		//assert(nodes[0] == edges[0]->getStartNode());
	}

	void createFaces(TriangleMesh& mesh, const float threshold, const MarchingCubeTable& mcTable)
	{
		const auto bit = getBit(threshold);
		const auto& triTable = mcTable.getTriangleTable();
		const auto& table = triTable[bit.to_ulong()];

		for (auto t : table.triangles) {
			auto e1 = edges[t.i1]->getVertex();
			auto e2 = edges[t.i2]->getVertex();
			auto e3 = edges[t.i3]->getVertex();
			mesh.createFace(e1, e2, e3);
		}

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


private:
	std::array<MCNode*, 8> nodes;
	std::array<MCEdge*, 12> edges;
};



class MCGrid
{
public:
	MCGrid(const float threshold) : threshold( threshold )
	{};
	
	void march(const Math::Volume3d<float, float>& volume);

	~MCGrid();

	void clear();

	std::vector< Vertex* > getVertices() const { return mesh.getVertices(); }

	TriangleMesh* cloneMesh() { return mesh.clone(); }

private:
	void createNodes(const Math::Volume3d<float, float>& volume);

	void createEdges(const Math::Volume3d<float, float>& volume);

	void createFaces(const Math::Volume3d<float, float>& volume);

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