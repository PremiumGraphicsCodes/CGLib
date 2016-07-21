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
	this->edges.insert(this->edges.end(), rhs.edges.begin(), rhs.edges.end());
	renumber();
	rhs.edges.clear();
}

Edge* EdgeCollection::create(Vertex* start, Vertex* end)
{
	auto e = new Edge(start, end, nextId++);
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

std::list<Edge*> EdgeCollection::getDegenerateds()
{
	std::list<Edge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated()) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}


void EdgeCollection::cleaning()
{
	auto shrinked = getDegenerateds();
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

Edge* EdgeCollection::findReverse(Edge* rhs)
{
	for (auto e : edges) {
		if (e->isReverse(*rhs)) {
			return e;
		}
	}
	return nullptr;
}
