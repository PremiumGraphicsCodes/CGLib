#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

#include <vector>

namespace Crystal {
	namespace Core {
		class Vertex;
		class HalfEdge;

class Edge
{
public:
	Edge(const int id = -1);

	Edge(HalfEdge* e1, const int id = -1);

	Edge(HalfEdge* e1, HalfEdge* e2, const int id = -1);

	void connect(Edge& next);

	std::vector<Edge> split(Vertex* v);

	Edge build(Vertex* v1, Vertex* v2);

	std::vector<Edge> createEdges(std::vector<Vertex*> vertices);

	//Edge clone();

	bool isShared() const;

	HalfEdge* getLeft() { return left; }

	HalfEdge* getRight() { return right; }

	void setId(const int id) { this->id = id; }

	int getId() const { return id; }

	void set(HalfEdge* left, HalfEdge* right);

	bool isLeft(const HalfEdge* e) const;

	bool isRight(const HalfEdge* e) const;

private:
	HalfEdge* left;
	HalfEdge* right;
	int id;
};

	}
}

#endif