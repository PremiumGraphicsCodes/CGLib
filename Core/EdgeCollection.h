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

	Edge* create(HalfEdge* e1, HalfEdge* v2);

	void clear();

	void cleaning();

	void renumber();

	void remove(Edge* e);

	Edge* findById(const int id);

	std::list<Edge*> get() const { return edges; }

	size_t size() const { return edges.size(); }

	using iterator = std::list<Edge*>::iterator;
	using const_iterator = std::list<Edge*>::const_iterator;

	iterator begin() { return edges.begin(); }

	const_iterator begin() const { return edges.begin(); }

	iterator end() { return edges.end(); }

	const_iterator end() const { return edges.end(); }

private:
	int nextId;
	std::list<Edge*> edges;
};

	}
}
#endif