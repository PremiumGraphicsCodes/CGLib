#include "stdafx.h"
#include "Surface.h"
#include "SimplificationAlgo.h"

using namespace Crystal::Core;

void SimplificationAlgo::execute(Edge* e)
{
	auto n1 = e->getStart();
	auto n2 = e->getEnd();
	auto center = e->getMidPoint();
	auto fs = surface->getFaces();
	for (auto f : fs) {
		if (f->has(e)) {
			factory->remove(f);
		}
	}
	factory->remove(e);
	n1->moveTo(center.getPosition());
	n2->moveTo(center.getPosition());
	/*
	for (auto f : fs) {
		f-> remove(f);
	}

	factory->remove(n2);
	*/
}
