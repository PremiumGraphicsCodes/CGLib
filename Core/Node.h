#ifndef __CRYSTAL_CORE_NODE_H__
#define __CRYSTAL_CORE_NODE_H__

#include "Vertex.h"

namespace Crystal {
	namespace Core {

class Node
{
public:
	Node() = default;

	Node(Vertex* v);

	void add(Vertex* v);

	Math::Point3d<float> merge();

private:
	std::list<Vertex*> vertices;
};
	}
}

#endif