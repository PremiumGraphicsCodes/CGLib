#ifndef __CRYSTAL_CORE_HALF_EDGE_REPOSITORY_H__
#define __CRYSTAL_CORE_HALF_EDGE_REPOSITORY_H__

#include "Vertex.h"
#include "HalfEdge.h"
#include "EdgeCollection.h"

namespace Crystal {
	namespace Core {

class HalfEdgeRepository
{
public:
	HalfEdgeRepository();

	HalfEdgeRepository(const std::vector<HalfEdge*>& edges);

	HalfEdgeRepository(const std::list<HalfEdge*>& edges);

	~HalfEdgeRepository();

	void merge(HalfEdgeRepository& rhs);

	HalfEdge* create(Vertex* v1, Vertex* v2);

	void clear();

	void cleaning();

	void renumber();

	void remove(HalfEdge* e);

	HalfEdge* findById(const int id);

	HalfEdge* findReverse(HalfEdge* e);

	std::list<HalfEdge*> get() const { return edges; }

	size_t size() const { return edges.size(); }

	std::list<HalfEdge*> findDegenerated();

	std::list<HalfEdge*> findDegenerated(const float length);

	std::list<HalfEdge*> findEdges(const Vertex* v);

	using iterator = std::list<HalfEdge*>::iterator;
	using const_iterator = std::list<HalfEdge*>::const_iterator;

	iterator begin() { return edges.begin(); }

	const_iterator begin() const { return edges.begin(); }

	iterator end() { return edges.end(); }

	const_iterator end() const { return edges.end(); }

	void setPairs();

private:
	int nextId;
	std::list<HalfEdge*> edges;
};

	}
}
#endif