#ifndef __CRYSTAL_CORE_LOOP_H__
#define __CRYSTAL_CORE_LOOP_H__

#include "Edge.h"
#include "Vertex.h"
#include <list>

namespace Crystal {
	namespace Core {

class Loop
{
public:
	Loop(const std::vector<Math::Vector3d<float>>& positions);

	~Loop() { clear();  }

	void clear();

	std::list<Vertex*> findConvex();

	bool isConvex(Edge* v);

	//float getArea() const;

	std::list<Face*> toFaces();

	std::vector<Edge*> getEdges() const { return edges; }

	std::vector<Vertex*> getVertices() const { return vertices; }

private:
	std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;
};
	}
}

#endif