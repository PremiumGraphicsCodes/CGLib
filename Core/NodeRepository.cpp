#include "stdafx.h"
#include "Vertex.h"
#include "NodeRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

NodeRepository::NodeRepository()
	: nextId(0)
{}

NodeRepository::NodeRepository(const std::vector<Vertex*>& vertices) :
	nextId(0)
{
	for (auto v : vertices) {
		nodes.push_back(new Node(v));
	}
}

NodeRepository::NodeRepository(const std::list<Vertex*>& vertices) :
	nextId(0)
{
	for (auto v : vertices) {
		nodes.push_back(new Node(v));
	}
}

NodeRepository::~NodeRepository()
{
}

void NodeRepository::merge(NodeRepository& rhs)
{
	nodes.insert(nodes.end(), rhs.nodes.begin(), rhs.nodes.end());
	rhs.nodes.clear();
}

void NodeRepository::clear()
{
	for (auto v : nodes) {
		delete v;
	}
	nodes.clear();
}

void NodeRepository::add(Node* n)
{
	nodes.push_back(n);
}

void NodeRepository::remove(Node* n)
{
	nodes.remove(n);
	delete n;
}
