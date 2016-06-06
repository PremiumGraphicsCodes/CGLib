#ifndef __CRYSTAL_CORE_SURFACE_H__
#define __CRYSTAL_CORE_SURFACE_H__

#include "../Math/Curve3d.h"

#include <list>
//#include "Node.h"

namespace Crystal {
	namespace Core {
		class Face;
		class Edge;
		class Node;

class Surface
{
public:
	Surface();

	explicit Surface(const Math::Curve3d<float>& curve);

	~Surface();

	void clear();

private:
	int nextNodeId;
	int nextEdgeId;
	int nextFaceId;
	std::list<Face*> faces;
	std::list<Edge*> edges;
	std::list<Node*> nodes;
};
	}
}

#endif
