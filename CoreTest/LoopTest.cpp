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

TEST(LoopTest, TestFindEar)
{
	std::vector<Vector3d<float>> positions;
	positions.push_back(Vector3d<float>(0, 0, 0));
	positions.push_back(Vector3d<float>(1, 0, 0));
	positions.push_back(Vector3d<float>(1, 1, 0));

	positions.push_back(Vector3d<float>(2, 1, 0));
	positions.push_back(Vector3d<float>(2, 2, 0));
	positions.push_back(Vector3d<float>(0, 2, 0));

	Loop loop(positions);
	const auto& actual = loop.findEar();
	EXPECT_EQ(1, actual.size());
	EXPECT_EQ(Vector3d<float>(2, 1, 0), actual.front()->getPosition());
}

TEST(LoopTest, TestSplit)
{
	std::vector<Vector3d<float>> positions;
	positions.push_back(Vector3d<float>(0, 0, 0));
	positions.push_back(Vector3d<float>(1, 0, 0));
	positions.push_back(Vector3d<float>(1, 1, 0));
	positions.push_back(Vector3d<float>(0, 1, 0));

	Loop loop(positions);
	auto vs = loop.getVertices();
	loop.split(vs[0], vs[2]);
	EXPECT_EQ(6, loop.getEdges().size());
//	EXPECT_EQ(1, actual.size());
//	EXPECT_EQ(Vector3d<float>(2, 1, 0), actual.front()->getPosition());
}