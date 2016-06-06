#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

namespace Crystal {
	namespace Core {

class Node;

class Edge
{
public:
	Node* start;
	Node* end;
};
	}
}

#endif