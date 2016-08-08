#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

#include <vector>

namespace Crystal {
	namespace Core {
		class Vertex;
		class HalfEdge;

class Edge
{
public:
	Edge();

	Edge(HalfEdge* e1);

	Edge(HalfEdge* e1, HalfEdge* e2);

	std::vector<Edge> split(Vertex* v);

	Edge build(Vertex* v1, Vertex* v2);

	std::vector<Edge> createEdges(std::vector<Vertex*> vertices);

	//Edge clone();

private:
	HalfEdge* e1;
	HalfEdge* e2;
};

	}
}

#endif