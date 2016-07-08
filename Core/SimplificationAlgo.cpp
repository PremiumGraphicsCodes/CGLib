#include "stdafx.h"
#include "Surface.h"
#include "SimplificationAlgo.h"

using namespace Crystal::Core;

void SimplificationAlgo::execute(Edge* e)
{
	auto prev = e->getPrev();
	auto n1 = e->getStart();
	auto n2 = e->getEnd();
	auto center = e->getMidPoint();
	auto fs = surface->getFaces();
	for (auto f : fs) {
		if (f->has(e)) {
			factory->remove(f);
		}
	}
	auto e2 = surface->findShared(e);
	factory->remove(e);
	factory->remove(e2);
	n1->moveTo(center.getPosition());
	surface->remove(n1);
	for (auto f : surface->getFaces()) {
		assert(f->isConnected());
	}

	//n2->moveTo(center.getPosition());
	/*
	Edge* degeneratedEdge = nullptr;
	for (auto e : surface->getEdges()) {
		if (e->getLength() == 0.0f) {
			degeneratedEdge = e;
		}
	}
	*/
	/*
	for (auto f : fs) {
		f-> remove(f);
	}

	factory->remove(n2);
	*/
}
