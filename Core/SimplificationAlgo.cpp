#include "stdafx.h"
#include "Surface.h"
#include "SimplificationAlgo.h"

using namespace Crystal::Core;

void SimplificationAlgo::execute()
{
	const auto edges = surface->getEdges();
	auto minEdge = edges.front();
	for (auto e : edges) {
		if (minEdge->getLength() > e->getLength()) {
			minEdge = e;
		}
	}
	execute(minEdge);
}

void SimplificationAlgo::execute(Edge* e)
{
	auto n1 = e->getStart();
	auto n2 = e->getEnd();
	auto center = e->getMidPoint();
	n1->moveTo(center.getPosition());
	n2->moveTo(center.getPosition());

	for (auto f : surface->getFaces()) {
		if (f->isDegenerated()) {
			factory->remove(f);
			factory->remove(f->getEdges()[0]);
			factory->remove(f->getEdges()[1]);
			factory->remove(f->getEdges()[2]);
		}
	}
	factory->removeAndConnect(e);
	factory->remove(n2);
	factory->remove(e);
	factory->cleaning();
}
