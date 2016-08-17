#include "stdafx.h"
#include "HalfEdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

HalfEdgeCollection::HalfEdgeCollection() :
	nextId(0)
{}

HalfEdgeCollection::HalfEdgeCollection(const std::vector<HalfEdge*>& edges) :
	edges(edges.begin(), edges.end()),
	nextId(0)
{
	setPairs();
}

HalfEdgeCollection::HalfEdgeCollection(const std::list<HalfEdge*>& edges) :
	edges(edges),
	nextId(0)
{
	setPairs();
}

HalfEdgeCollection::~HalfEdgeCollection()
{
	//clear();
}

void HalfEdgeCollection::merge(HalfEdgeCollection& rhs)
{
	this->edges.splice(this->edges.end(), rhs.edges);
	renumber();
	rhs.edges.clear();
	setPairs();
}

HalfEdge* HalfEdgeCollection::create(Vertex* start, Vertex* end)
{
	auto e = new HalfEdge(start, end, nextId++);
	edges.push_back(e);
	return e;
}

void HalfEdgeCollection::clear()
{
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
}

std::list<HalfEdge*> HalfEdgeCollection::findDegenerated()
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated()) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> HalfEdgeCollection::findDegenerated(const float length)
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated(length)) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> HalfEdgeCollection::findEdges(const Vertex* v)
{
	std::list<HalfEdge*> results;
	for (auto e : edges) {
		if (e->getStart() == v) {
			results.push_back(e);
		}
	}
	return results;
}


void HalfEdgeCollection::cleaning()
{
	auto shrinked = findDegenerated();
	for (auto f : shrinked) {
		remove(f);
	}
	renumber();
}

void HalfEdgeCollection::renumber()
{
	nextId = 0;
	for (auto e : edges) {
		e->setId(nextId++);
	}

}

void HalfEdgeCollection::remove(HalfEdge* e)
{
	edges.remove(e);
	delete e;
}

HalfEdge* HalfEdgeCollection::findById(const int id)
{
	for (auto f : edges) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}

HalfEdge* HalfEdgeCollection::findReverse(HalfEdge* rhs)
{
	return rhs->getPair();
}

void HalfEdgeCollection::setPairs()
{
	std::vector<HalfEdge*> es( edges.begin(), edges.end() );
	std::sort(es.begin(), es.end(),
		[](HalfEdge* lhs, HalfEdge* rhs) { return lhs->getHashKey() < rhs->getHashKey(); }
	);
	for (int i = 0; i < es.size()-1; ++i) {
		auto e1 = es[i];
		auto e2 = es[i + 1];
		if (e1->getHashKey() == e2->getHashKey()) {
			e1->setPair(e2);
			e2->setPair(e1);
		}
	}
}
