#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Core {

class Node;

class Edge : private UnCopyable
{
public:
	Edge(Node* start, Node* end, int id);

private:
	Node* start;
	Node* end;
	int id;
};
	}
}

#endif