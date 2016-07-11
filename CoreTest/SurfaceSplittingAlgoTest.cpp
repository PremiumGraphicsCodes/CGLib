#include "stdafx.h"
#include "../Core/Surface.h"
#include "../Core/SurfaceSplittingAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceSplittingAlgoTest, TestSplitByNode)
{
	const Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const TriangleCurve3d<float> curve = triangle.toCurve3d();

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitter(surface, &factory);
	splitter.splitByNode(f);

	EXPECT_EQ(surface->getNodes().size(), 6);
	EXPECT_EQ(surface->getFaces().size(), 4);
	EXPECT_EQ(surface->getEdges().size(), 12);
}

TEST(SurfaceSplittingAlgoTest, TestSplitByCenter)
{
	const Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const TriangleCurve3d<float> curve = triangle.toCurve3d();

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitter(surface, &factory);
	splitter.splitByCenter(f);
	factory.cleaning();
	EXPECT_EQ(surface->getFaces().size(), 3);
	EXPECT_EQ(surface->getNodes().size(), 4);
}

TEST(SurfaceSplittingAlgoTest, TestSplitByBottom)
{
	const Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const TriangleCurve3d<float> curve = triangle.toCurve3d();

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo algo(surface, &factory);
	algo.splitByBottom(f);
	EXPECT_EQ(2, surface->getFaces().size());
	EXPECT_EQ(4, surface->getNodes().size());
	EXPECT_EQ(6, surface->getEdges().size());
}