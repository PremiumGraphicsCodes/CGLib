#include "stdafx.h"
#include "HalfEdgeRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

HalfEdgeRepository::HalfEdgeRepository() :
	nextId(0)
{}

HalfEdgeRepository::HalfEdgeRepository(const std::vector<HalfEdge*>& edges) :
	edges(edges.begin(), edges.end()),
	nextId(0)
{
	setPairs();
}

HalfEdgeRepository::HalfEdgeRepository(const std::list<HalfEdge*>& edges) :
	edges(edges),
	nextId(0)
{
	setPairs();
}

HalfEdgeRepository::~HalfEdgeRepository()
{
	//clear();
}

void HalfEdgeRepository::merge(HalfEdgeRepository& rhs)
{
	this->edges.splice(this->edges.end(), rhs.edges);
	renumber();
	rhs.edges.clear();
	setPairs();
}

HalfEdge* HalfEdgeRepository::create(Vertex* start, Vertex* end)
{
	auto e = new HalfEdge(start, end, nextId++);
	edges.push_back(e);
	return e;
}

void HalfEdgeRepository::clear()
{
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
}

std::list<HalfEdge*> HalfEdgeRepository::findDegenerated()
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated()) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> HalfEdgeRepository::findDegenerated(const float length)
{
	std::list<HalfEdge*> shrinked;
	for (auto e : edges) {
		if (e->isDegenerated(length)) {
			shrinked.push_back(e);
		}
	}
	return shrinked;
}

std::list<HalfEdge*> HalfEdgeRepository::findEdges(const Vertex* v)
{
	std::list<HalfEdge*> results;
	for (auto e : edges) {
		if (e->getStart() == v) {
			results.push_back(e);
		}
	}
	return results;
}


void HalfEdgeRepository::cleaning()
{
	auto shrinked = findDegenerated();
	for (auto f : shrinked) {
		remove(f);
	}
	renumber();
}

void HalfEdgeRepository::renumber()
{
	nextId = 0;
	for (auto e : edges) {
		e->setId(nextId++);
	}

}

void HalfEdgeRepository::remove(HalfEdge* e)
{
	edges.remove(e);
	delete e;
}

HalfEdge* HalfEdgeRepository::findById(const int id)
{
	for (auto f : edges) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}

HalfEdge* HalfEdgeRepository::findReverse(HalfEdge* rhs)
{
	return rhs->getPair();
}

void HalfEdgeRepository::setPairs()
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
