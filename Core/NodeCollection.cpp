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


Node* NodeCollection::create(const Point3d<float>& p)
{
	auto n = new Node(p.getPosition(), p.getNormal(), nextId++);
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

void NodeCollection::remove(Node* n)
{
	auto found = std::find(nodes.begin(), nodes.end(), n);
	delete n;
	nodes.remove(n);
}

Node* NodeCollection::findById(const int id) const
{
	for (auto e : nodes) {
		if (e->getId() == id) {
			return e;
		}
	}
	return nullptr;

}
