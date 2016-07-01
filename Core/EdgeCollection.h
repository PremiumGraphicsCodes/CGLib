#ifndef __CRYSTAL_CORE_EDGE_COLLECTION_H__
#define __CRYSTAL_CORE_EDGE_COLLECTION_H__

#include <vector>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Core {
		class Edge;
		class Node;

class EdgeCollection : private UnCopyable
{
public:
	EdgeCollection();

	~EdgeCollection();

	void clear();

	Edge* create(Node* start, Node* end);

	std::list<Edge*> get() { return edges; }

	void merge(EdgeCollection& rhs);

private:
	int nextId;
	std::list<Edge*> edges;
};
	}
}

#endif