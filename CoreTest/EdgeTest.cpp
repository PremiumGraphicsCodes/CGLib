#include "stdafx.h"

#include "../Core/Node.h"
#include "../Core/Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeTest, TestGetVector)
{
	Node n1(Vector3d<float>(0, 0, 0), 0);
	Node n2(Vector3d<float>(1, 0, 0), 1);
	Edge e(&n1, &n2, 0);
	EXPECT_EQ(Vector3d<float>(1,0,0), e.getVector());
}

TEST(EdgeTest, TestGetLength)
{
	Node n1(Vector3d<float>(0,0,0),0);
	Node n2(Vector3d<float>(1,0,0),1);
	Edge e(&n1, &n2, 0);
	EXPECT_EQ(1, e.getLength());
}

TEST(EdgeTest, TestIsReverse)
{
	Node n1(Vector3d<float>(0, 0, 0), 0);
	Node n2(Vector3d<float>(1, 0, 0), 1);
	Node n3(Vector3d<float>(2, 0, 0), 2);
	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n1, 0);
	Edge e3(&n3, &n1, 0);
	EXPECT_TRUE(e1.isReverse(e2));
	EXPECT_TRUE(e2.isReverse(e1));
	EXPECT_FALSE(e1.isReverse(e3));

}

TEST(EdgeTest, TestIsShared)
{
	Node n1(Vector3d<float>(0, 0, 0), 0);
	Node n2(Vector3d<float>(1, 0, 0), 1);
	Node n3(Vector3d<float>(2, 0, 0), 2);
	const Edge e1(&n1, &n2, 0);
	const Edge e2(&n2, &n1, 0);
	const Edge e3(&n3, &n1, 0);

	EXPECT_TRUE( e1.isShared(e2));
	EXPECT_FALSE(e1.isShared(e3));
}

TEST(EdgeTest, TestIsCollapsed)
{
	Node n1(Vector3d<float>(0, 0, 0), 0);
	Node n2(Vector3d<float>(1, 0, 0), 1);
	const Edge e1(&n1, &n2, 0);
	const Edge e2(&n1, nullptr, 0);
	EXPECT_FALSE(e1.isCollapsed());
	EXPECT_TRUE( e2.isCollapsed());
}