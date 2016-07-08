#include "stdafx.h"
#include "../Core/Surface.h"
#include "../Core/SurfaceSplittingAlgo.h"
#include "../Core/SmoothingAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SmoothingAlgoTest, Test)
{
	const Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const auto& curve = triangle.toCurve3d();
	
	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitAlgo(surface, &factory);
	splitAlgo.splitByCenter(f);
	SmoothingAlgo smoothingAlgo(surface, &factory);
	auto n = surface->getNodes().back();
	n->moveTo(Vector3d<float>(1, 0, 0));
	smoothingAlgo.execute(n);
	EXPECT_EQ(Vector3d<float>(0.25, 0.25, 0), n->getPosition());
}