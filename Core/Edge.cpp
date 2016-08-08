#include "stdafx.h"
#include "Edge.h"
#include "HalfEdge.h"

using namespace Crystal::Core;

Edge::Edge() :
	e1(nullptr),
	e2(nullptr)
{
}

Edge::Edge(HalfEdge* e1) :
	e1(e1),
	e2(nullptr)
{}

Edge::Edge(HalfEdge* e1, HalfEdge* e2) :
	e1(e1),
	e2(e2)
{}

std::vector<Edge> Edge::split(Vertex* v)
{
	auto v1 = e1->getStart();
	auto v2 = e2->getEnd();
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
	std::vector<Edge> results;
	for (int i = 0; i < vertices.size() - 1; ++i) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		auto e = build(v1, v2);
		results.push_back(e);
	}
	return results;
}
