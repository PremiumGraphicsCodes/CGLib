#include "stdafx.h"
#include "EdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

EdgeCollection::EdgeCollection() :
	nextId(0)
{}

EdgeCollection::EdgeCollection(const std::vector<Edge*>& edges) :
	edges(edges.begin(), edges.end()),
	nextId(0)
{
}

EdgeCollection::EdgeCollection(const std::list<Edge*>& edges) :
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

Edge* EdgeCollection::create(HalfEdge* e1, HalfEdge* e2)
{
	auto e = new Edge(e1, e2, nextId++);
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

void EdgeCollection::cleaning()
{
	renumber();
}

void EdgeCollection::renumber()
{
	nextId = 0;
	for (auto e : edges) {
		e->setId(nextId++);
	}
}

void EdgeCollection::remove(Edge* e)
{
	edges.remove(e);
	delete e;
}

Edge* EdgeCollection::findById(const int id)
{
	for (auto f : edges) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}
