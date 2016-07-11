#include "stdafx.h"
#include "NodeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

NodeCollection::NodeCollection() :
	nextId(0)
{
}

NodeCollection::~NodeCollection()
{
	clear();
}


void NodeCollection::clear()
{
	for (auto n : nodes) {
		delete n;
	}
	nodes.clear();
	nextId = 0;
}


Vertex* NodeCollection::create(const Point3d<float>& p)
{
	auto n = new Vertex(p.getPosition(), p.getNormal(), nextId++);
	nodes.push_back(n);
	return n;
}

void NodeCollection::merge(NodeCollection& rhs)
{
	for (auto n : rhs.nodes) {
		n->setId(nextId++);
	}
	nodes.insert(nodes.end(), rhs.nodes.begin(), rhs.nodes.end());
	rhs.nodes.clear();
}

void NodeCollection::remove(Vertex* n)
{
	auto found = std::find(nodes.begin(), nodes.end(), n);
	*found = nullptr;
}

Vertex* NodeCollection::findById(const int id) const
{
	for (auto e : nodes) {
		if (e->getId() == id) {
			return e;
		}
	}
	return nullptr;
}

void NodeCollection::renumber()
{
	nextId = 0;
	for (auto n : nodes) {
		n->setId(nextId++);
	}
}

void NodeCollection::cleaning()
{
	nodes.remove(nullptr);
	renumber();
}