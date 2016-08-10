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
	findPair();
}

HalfEdgeCollection::HalfEdgeCollection(const std::list<HalfEdge*>& edges) :
	edges(edges),
	nextId(0)
{
	findPair();
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
	findPair();
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
	for (auto e : edges) {
		if (e->isReverse(*rhs)) {
			return e;
		}
	}
	return nullptr;
}

#include "EdgeSpaceHash.h"

void HalfEdgeCollection::findPair()
{
	float averagedLength = 0.0f;
	for (auto e : edges) {
		averagedLength += (e->getLength() / static_cast<float>(edges.size()));
	}
	EdgeSpaceHash hash(averagedLength, edges.size());
	for (auto e : edges) {
		hash.add(e);
	}
	for (auto e : edges) {
		const auto& neighbors = hash.getNeighbor(e->getEnd()->getPosition());
		for (auto n : neighbors) {
			if (n->isReverse(*e)) {
				e->setPair(n);
				n->setPair(e);
			}
		}
	}
}
