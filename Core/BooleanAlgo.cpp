#include "stdafx.h"
#include "BooleanAlgo.h"
#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

BooleanAlgo::BooleanAlgo(Surface* surface1, Surface* surface2) :
	surface1(surface1),
	surface2(surface2)
{}

Intersection3d<float> BooleanAlgo::findIntersections()
{
	auto faces1 = surface1->getFaces();
	std::vector<Triangle3d<float>> triangles1;
	for (auto f : faces1) {
		triangles1.push_back( f->toTriangle() );
	}
	auto faces2 = surface2->getFaces();
	std::vector<Triangle3d<float>> triangles2;
	for (auto f : faces2) {
		triangles2.push_back(f->toTriangle());
	}

	for (const auto& t1 : triangles1) {
		for (const auto& t2 : triangles2) {
			intersection.calculate(t1, t2);
		}
	}
	return intersection;
}
