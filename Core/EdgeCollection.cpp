#include "stdafx.h"
#include "EdgeCollection.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

EdgeCollection::EdgeCollection() :
	nextId(0)
{
}

EdgeCollection::~EdgeCollection()
{
	//clear();
}

void EdgeCollection::clear()
{
	for (auto n : edges) {
		delete n;
	}
	edges.clear();
	nextId = 0;

}

Edge* EdgeCollection::create(Vertex* start, Vertex* end)
{
	auto e = new Edge(start, end, nextId++);
	edges.push_back(e);
	return e;
}

void EdgeCollection::merge(EdgeCollection& rhs)
{
	for (auto n : rhs.edges) {
		n->setId(nextId++);
	}

	edges.insert(edges.end(), rhs.edges.begin(), rhs.edges.end());
	rhs.edges.clear();
}

void EdgeCollection::remove(Edge* e)
{
	auto found = std::find(edges.begin(), edges.end(), e);
	if (found != edges.end()) {
		*found = nullptr;
	}
}

Edge* EdgeCollection::findById(const int id) const
{
	for (auto e : edges) {
		if (e->getId() == id) {
			return e;
		}
	}
	return nullptr;
}

void EdgeCollection::renumber()
{
	nextId = 0;
	for (auto e : edges) {
		e->setId(nextId++);
	}
}

void EdgeCollection::cleaning()
{
	edges.remove(nullptr);
	renumber();
}
