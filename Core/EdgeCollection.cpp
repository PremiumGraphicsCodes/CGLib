#include "stdafx.h"
#include "EdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

EdgeCollection::EdgeCollection() :
	nextId(0)
{}

EdgeCollection::EdgeCollection(const std::vector<HalfEdge*>& edges) :
	edges(edges.begin(), edges.end()),
	nextId(0)
{

}


EdgeCollection::EdgeCollection(const std::list<HalfEdge*>& edges) :
	edges(edges),
	nextId(0)
{}

EdgeCollection::~EdgeCollection()
{
	//clear();
}

void EdgeCollection::merge(EdgeCollection& rhs)
{
	this->edges.splice(this->edges.end(), rhs.edges);
	renumber();
	rhs.edges.clear();
}

HalfEdge* EdgeCollection::create(Vertex* start, Vertex* end)
{
	auto e = new HalfEdge(start, end, nextId++);
	edges.push_back(e);
	return e;
}

void EdgeCollection::clear()
{
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
}

std::list<HalfEdge*> EdgeCollection::findDegenerated()
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated()) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> EdgeCollection::findDegenerated(const float length)
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated(length)) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> EdgeCollection::findEdges(const Vertex* v)
{
	std::list<HalfEdge*> results;
	for (auto e : edges) {
		if (e->getStart() == v) {
			results.push_back(e);
		}
	}
	return results;
}


void EdgeCollection::cleaning()
{
	auto shrinked = findDegenerated();
	for (auto f : shrinked) {
		remove(f);
	}
	renumber();
}

void EdgeCollection::renumber()
{
	nextId = 0;
	for (auto e : edges) {
		e->setId(nextId++);
	}

}

void EdgeCollection::remove(HalfEdge* e)
{
	edges.remove(e);
	delete e;
}

HalfEdge* EdgeCollection::findById(const int id)
{
	for (auto f : edges) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}

HalfEdge* EdgeCollection::findReverse(HalfEdge* rhs)
{
	for (auto e : edges) {
		if (e->isReverse(*rhs)) {
			return e;
		}
	}
	return nullptr;
}
