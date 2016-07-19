#ifndef __CRYSTAL_CORE_EDGE_COLLECTION_H__
#define __CRYSTAL_CORE_EDGE_COLLECTION_H__

#include "Vertex.h"
#include "Edge.h"

namespace Crystal {
	namespace Core {

class EdgeCollection
{
public:
	EdgeCollection();

	EdgeCollection(const std::vector<Edge*>& edges);

	EdgeCollection(const std::list<Edge*>& edges);

	~EdgeCollection();

	void merge(EdgeCollection& rhs);

	Edge* create(Vertex* v1, Vertex* v2);

	void clear();

	void cleaning();

	void renumber();

	void remove(Edge* e);

	Edge* findById(const int id);

private:
	int nextId;
	std::list<Edge*> edges;
};

	}
}
#endif