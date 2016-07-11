#include "stdafx.h"

#include "../Core/Surface.h"
#include "../Core/SurfaceFactory.h"
#include "../Core/SurfaceRemoveAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceRemoveAlgoTest, TestRemoveEdge)
{
	SurfaceFactory factory;
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	auto s = factory.create( triangle.toCurve3d() );
	SurfaceRemoveAlgo algo(&factory);
	auto edge = s->getEdges().front();
	algo.add(edge);
	algo.execute();
	EXPECT_TRUE( factory.getFaces().empty() );
	EXPECT_TRUE( factory.getEdges().empty());
}