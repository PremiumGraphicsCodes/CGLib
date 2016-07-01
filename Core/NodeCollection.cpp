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
