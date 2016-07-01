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

Edge* EdgeCollection::create(Node* start, Node* end)
{
	auto e = new Edge(start, end, nextId++);
	edges.push_back(e);
	return e;
}
