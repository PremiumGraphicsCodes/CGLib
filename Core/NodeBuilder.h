#ifndef __CRYSTAL_CORE_NODE_BUILDER_H__
#define __CRYSTAL_CORE_NODE_BUILDER_H__

#include <list>

namespace Crystal {
	namespace Core {
		class Vertex;
		class Node;

class NodeBuilder
{
public:
	explicit NodeBuilder(const std::list<Vertex*>& vertices);

	std::list<Node*> build(const float distance);

private:
	std::list<Vertex*> vertices;
};
	}
}

#endif