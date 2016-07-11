#include "stdafx.h"
#include "ReductionAlgo.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

float ReductionAlgo::getCollapseCost(Edge* edge)
{
	auto n1 = edge->getStart();
	auto n2 = edge->getEnd();
	auto length = edge->getLength();
	float curvature = 0;

	/*
	Face* sides;
	for (auto f : edge->getFace()) {

	}
	*/
	return 0;
}
