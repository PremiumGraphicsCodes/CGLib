#include "stdafx.h"
#include "../Core/SimplificationAlgo.h"
#include "../Core/SurfaceSplittingAlgo.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SimplificationAlgoTest, Test)
{
	const Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const TriangleCurve3d<float> curve = triangle.toCurve3d();

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitter(surface, &factory);
	splitter.splitByBottom(f);
	SimplificationAlgo algo(surface, &factory);
	auto e = surface->getFaces().front()->getEdges().back();
	algo.execute(e);
	EXPECT_EQ(1, surface->getFaces().size());
	EXPECT_EQ(3, surface->getNodes().size());
	//EXPECT_EQ(3, surface->getEdges().size());
}