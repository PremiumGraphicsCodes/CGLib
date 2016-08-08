#include "stdafx.h"
#include "Edge.h"
#include "HalfEdge.h"

using namespace Crystal::Core;

Edge::Edge(const int id) :
	left(nullptr),
	right(nullptr),
	id(id)
{
}

Edge::Edge(HalfEdge* e1, const int id) :
	left(e1),
	right(nullptr),
	id(id)
{}

Edge::Edge(HalfEdge* e1, HalfEdge* e2, const int id) :
	left(e1),
	right(e2),
	id(id)
{}

void Edge::connect(Edge& next)
{
	left->connect(next.left);
	next.right->connect(right);
}


std::vector<Edge> Edge::split(Vertex* v)
{
	auto v1 = left->getStart();
	auto v2 = left->getEnd();
	return createEdges(std::vector<Vertex*>{ v1, v, v2 });
}

Edge Edge::build(Vertex* v1, Vertex* v2)
{
	auto e1 = new HalfEdge(v1, v2);
	auto e2 = new HalfEdge(v2, v1);
	return Edge(e1, e2);
}

std::vector<Edge> Edge::createEdges(std::vector<Vertex*> vertices)
{
	std::vector<Edge> edges;
	for (int i = 0; i < vertices.size() - 1; ++i) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		auto e = build(v1, v2);
		edges.push_back(e);
	}
	for (int i = 0; i < edges.size() - 1; ++i) {
		auto e1 = edges[i];
		auto e2 = edges[i + 1];
		e1.connect(e2);
	}
	return edges;
}

bool Edge::isShared() const
{
	return left && right;
}
