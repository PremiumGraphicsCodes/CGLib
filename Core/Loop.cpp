#include "stdafx.h"
#include "Loop.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Loop::Loop(const std::vector<Vector3d<float>>& positions)
{
	for (int i = 0; i < positions.size(); ++i) {
		vertices.push_back(new Vertex(positions[i]));
	}
	for (int i = 0; i < vertices.size() - 1; ++i) {
		Vertex* v1 = vertices[i];
		Vertex* v2 = vertices[i + 1];
		auto e = new Edge(v1, v2);
		edges.push_back(e);
	}
	edges.push_back(new Edge(vertices.back(), vertices.front()));
	for (int i = 0; i < edges.size() - 1; ++i) {
		Edge* e1 = edges[i];
		Edge* e2 = edges[i + 1];
		e1->connect(e2);
	}
	edges.back()->connect(edges.front());
}

void Loop::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
}

bool Loop::isConvex(Edge* e)
{
	const auto& v1 = e->getVector().normalized();
	const auto& v2 = e->getNext()->getVector().normalized();
	const auto& angle = v1.getAngle(v2);
	return angle.getRadian().get() > Tolerance<float>::getPI();
}

std::list<Vertex*> Loop::findConvex()
{
	std::list<Vertex*> results;
	for (auto e : edges) {
		if (isConvex(e)) {
			results.push_back(e->getEnd());
		}
	}
	return results;
}

/*
float Loop::getArea() const
{
	for (int i = 0; i < vertices.size() - 1; ++i) {
		vertices[i] - vetices[i - 1];
	}
}
*/
