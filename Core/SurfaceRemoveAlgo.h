#ifndef __CRYSTAL_CORE_SURFACE_REMOVE_ALGO__
#define __CRYSTAL_CORE_SURFACE_REMOVE_ALGO__

#include <list>

namespace Crystal {
	namespace Core {
		class Node;
		class Edge;
		class Face;
		class Surface;
		class SurfaceFactory;

class SurfaceRemoveAlgo
{
public:
	SurfaceRemoveAlgo(SurfaceFactory* factory);

	void add(Face *f);

	void add(Edge* e);

	void add(Node* n);

	void execute();

private:
	SurfaceFactory* factory;
	std::list<Face*> faces;
	std::list<Edge*> edges;
	std::list<Node*> nodes;
};
	}
}

#endif