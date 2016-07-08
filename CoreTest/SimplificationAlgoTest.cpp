#include "stdafx.h"
#include "../Core/SimplificationAlgo.h"
#include "../Core/SurfaceSplittingAlgo.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SimplificationAlgoTest, Test)
{
	const Quad<float> quad(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const auto& curve = quad.toCurve3d();

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto e = surface->getFaces().front()->getEdges().back();
	SimplificationAlgo algo(surface, &factory);
	algo.execute(e);
	EXPECT_EQ(1, surface->getFaces().size());
}