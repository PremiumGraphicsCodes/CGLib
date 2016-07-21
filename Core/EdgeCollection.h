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

	Edge* findReverse(Edge* e);

	std::list<Edge*> get() const { return edges; }

	size_t size() const { return edges.size(); }

	std::list<Edge*> getDegenerateds();

private:
	int nextId;
	std::list<Edge*> edges;
};

	}
}
#endif