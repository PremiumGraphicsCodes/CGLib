#include "stdafx.h"
#include "Loop.h"
#include "Face.h"

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
		auto e = new HalfEdge(v1, v2);
		edges.push_back(e);
	}
	edges.push_back(new HalfEdge(vertices.back(), vertices.front()));
	for (int i = 0; i < edges.size() - 1; ++i) {
		HalfEdge* e1 = edges[i];
		HalfEdge* e2 = edges[i + 1];
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
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}

bool Loop::isConvex(HalfEdge* e)
{
	const auto& v1 = e->getVector().normalized();
	const auto& v2 = e->getNext()->getVector().normalized();
	return (v1.getOuterProduct(v2).getZ() > 0);
	//const auto& angle = v1.getAngle(v2);
	//return angle.getRadian().get() > Tolerance<float>::getPI();
}

bool Loop::isReflex(HalfEdge* e)
{
	return !isConvex(e);
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

std::list<Vertex*> Loop::findReflex()
{
	std::list<Vertex*> results;
	for (auto e : edges) {
		if (isReflex(e)) {
			results.push_back(e->getEnd());
		}
	}
	return results;

}


std::list<Vertex*> Loop::findEar()
{
	std::list<Vertex*> results;
	for (auto e : edges) {
		auto prev = e;
		auto next = e->getNext();
		if (isReflex(prev) && isConvex(next)) {
			results.push_back(next->getEnd());
		}
	}
	return results;

}

void Loop::remove(Vertex* v)
{
	/*
	auto e = findStartEdge(v);
	auto e1 = e->getPrev();
	auto e2 = e1->getNext();
	auto e3 = e2->getNext();
	auto e4 = e3->getNext();

	auto e = new Edge(v, e3->getEnd());
	edges.push_back(e);
	e1->connect(e);
	*/
}

HalfEdge* Loop::findStartEdge(Vertex* v)
{
	for (auto e : edges) {
		if (e->getStart() == v) {
			return e;
		}
	}
	return nullptr;
}

std::array<HalfEdge*, 3> Loop::getFace(Vertex* center)
{
	//std::array<Edge*, 3> face;
	auto e1 = findStartEdge(center);
	auto e0 = e1->getPrev();
	auto e2 = new HalfEdge(e1->getEnd(), e0->getStart());
	edges.push_back(e2);
	return{ e0, e1, e2 };
}


void Loop::split(Vertex* start, Vertex* end)
{
	auto e1 = new HalfEdge(end, start);
	edges.push_back(e1);
	auto e2 = findStartEdge(start);
	auto e3 = e2->getNext();
	auto f = new Face(e1, e2, e3);
	faces.push_back(f);
	auto e4 = new HalfEdge(start, end);
	edges.push_back(e4);
	auto prev = e2->getPrev();
	auto next = e3->getNext();
	prev->connect(e4);
	e4->connect(next);
}

/*

float Loop::getArea() const
{
	for (int i = 0; i < vertices.size() - 1; ++i) {
		vertices[i] - vetices[i - 1];
	}
}
*/
