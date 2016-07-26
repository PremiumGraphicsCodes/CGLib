#include "stdafx.h"

#include "../Core/Loop.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(LoopTest, TestConstruct)
{
	std::vector<Vector3d<float>> positions;
	positions.push_back( Vector3d<float>(0, 0, 0) );
	positions.push_back( Vector3d<float>(1, 0, 0) );
	positions.push_back( Vector3d<float>(1, 1, 0) );
	positions.push_back( Vector3d<float>(0, 1, 0));

	Loop loop(positions);
	EXPECT_EQ(4, loop.getEdges().size());
	EXPECT_EQ(4, loop.getVertices().size());
}

TEST(LoopTest, TestFindConvex)
{
	std::vector<Vector3d<float>> positions;
	positions.push_back(Vector3d<float>(0, 0, 0));
	positions.push_back(Vector3d<float>(1, 0, 0));
	positions.push_back(Vector3d<float>(1,-1, 0));

	positions.push_back(Vector3d<float>(2, 1, 0));
	positions.push_back(Vector3d<float>(0, 1, 0));

	Loop loop(positions);
	const auto& actual = loop.findConvex();
	EXPECT_EQ(4, actual.size());
}