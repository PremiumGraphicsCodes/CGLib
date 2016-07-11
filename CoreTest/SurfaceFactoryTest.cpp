#include "stdafx.h"
#include "../Core/SurfaceFactory.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceFactoryTest, TestRenumber)
{
	SurfaceFactory factory;
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	std::vector<Face*> faces;
	Triangle3d<float> triangle;
	auto s1 = factory.create(triangle.toCurve3d(), 2);
	auto s2 = factory.create(triangle.toCurve3d(), 4);
	factory.renumber();
	EXPECT_EQ(0, s1->getId());
	EXPECT_EQ(1, s2->getId());
}
