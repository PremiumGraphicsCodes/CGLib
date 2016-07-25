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

	std::list<Edge*> findDegenerated();

	std::list<Edge*> findDegenerated(const float length);

	std::list<Edge*> findEdges(const Vertex* v);


	using iterator = std::list<Edge*>::iterator;
	using const_iterator = std::list<Edge*>::const_iterator;

	iterator begin() { return edges.begin(); }

	//iterator front() { return faces.front(); }

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