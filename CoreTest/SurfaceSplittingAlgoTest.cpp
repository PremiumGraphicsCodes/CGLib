#include "stdafx.h"
#include "../Core/Surface.h"
#include "../Core/SurfaceSplittingAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceSplittingAlgoTest, TestSplitByNode)
{
	TriangleCurve3d<float> curve(2);

	Point3d<float> p1(Vector3d<float>(0, 1, 0));
	Point3d<float> p2(Vector3d<float>(-1, 0, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));

	curve.set(0, 0, p1);
	curve.set(1, 0, p2);
	curve.set(1, 1, p3);

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitter(surface, &factory);
	splitter.splitByNode(f);

	//	EXPECT_EQ(surface->getNodes().size(), 3);
	//	EXPECT_EQ(surface->getFaces().size(), 4);
	//	EXPECT_EQ(surface->getEdges().size(), 12);

}