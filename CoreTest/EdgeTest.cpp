#include "stdafx.h"

#include "../Core/Vertex.h"
#include "../Core/Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeTest, TestGetVector)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Edge e(&n1, &n2, 0);
	EXPECT_EQ(Vector3d<float>(1,0,0), e.getVector());
}

TEST(EdgeTest, TestGetLength)
{
	Vertex n1(Vector3d<float>(0,0,0),0);
	Vertex n2(Vector3d<float>(1,0,0),1);
	Edge e(&n1, &n2, 0);
	EXPECT_EQ(1, e.getLength());
}

TEST(EdgeTest, TestIsReverse)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n1, 0);
	Edge e3(&n3, &n1, 0);
	EXPECT_TRUE(e1.isReverse(e2));
	EXPECT_TRUE(e2.isReverse(e1));
	EXPECT_FALSE(e1.isReverse(e3));

}

TEST(EdgeTest, TestIsShared)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	const Edge e1(&n1, &n2, 0);
	const Edge e2(&n2, &n1, 0);
	const Edge e3(&n3, &n1, 0);

	EXPECT_TRUE( e1.isShared(e2));
	EXPECT_FALSE(e1.isShared(e3));
}

TEST(EdgeTest, TestIsCollapsed)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	const Edge e1(&n1, &n2, 0);
	const Edge e2(&n1, nullptr, 0);
	EXPECT_FALSE(e1.isCollapsed());
	EXPECT_TRUE( e2.isCollapsed());
}

/*
#include "../Core/Face.h"

TEST(EdgeTest, TestCalculateCollapseCost)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(1, 1, 0), 1);
	Vertex n4(Vector3d<float>(-1, 1, 1), 1);

	Edge e1(&n1, &n2);
	Edge e2(&n2, &n3);
	Edge e3(&n3, &n1);

	Face f1(&e1, &e2, &e3);
	auto actual = e1.calculateCollapseCost();
	//Edge e3(&n4, &n1);

	const Edge e4(&n3, &n4, 0);
	EXPECT_FLOAT_EQ(e4.getLength(), e4.calculateCollapseCost());
}
*/