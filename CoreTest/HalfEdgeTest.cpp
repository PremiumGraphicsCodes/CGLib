#include "stdafx.h"

#include "../Core/Vertex.h"
#include "../Core/HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(HalfEdgeTest, TestGetVector)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e(&n1, &n2, 0);
	EXPECT_EQ(Vector3d<float>(1,0,0), e.getVector());
}

TEST(HalfEdgeTest, TestGetLength)
{
	Vertex n1(Vector3d<float>(0,0,0),0);
	Vertex n2(Vector3d<float>(1,0,0),1);
	HalfEdge e(&n1, &n2, 0);
	EXPECT_EQ(1, e.getLength());
}

TEST(HalfEdgeTest, TestIsReverse)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	HalfEdge e1(&n1, &n2, 0);
	HalfEdge e2(&n2, &n1, 0);
	HalfEdge e3(&n3, &n1, 0);
	EXPECT_TRUE(e1.isReverse(e2));
	EXPECT_TRUE(e2.isReverse(e1));
	EXPECT_FALSE(e1.isReverse(e3));
}

TEST(HalfEdgeTest, TestIsShared)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	const HalfEdge e1(&n1, &n2, 0);
	const HalfEdge e2(&n2, &n1, 0);
	const HalfEdge e3(&n3, &n1, 0);

	EXPECT_TRUE( e1.isShared(e2));
	EXPECT_FALSE(e1.isShared(e3));
}

TEST(HalfEdgeTest, TestIsCollapsed)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	const HalfEdge e1(&n1, &n2, 0);
	const HalfEdge e2(&n1, nullptr, 0);
	EXPECT_FALSE(e1.isCollapsed());
	EXPECT_TRUE( e2.isCollapsed());
}

TEST(HalfEdgeTest, TestIsDegenerated)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(0, 0, 0), 1);
	const HalfEdge e1(&n1, &n2, 0);
	EXPECT_TRUE(e1.isDegenerated());
	n2.moveTo(Vector3d<float>(1, 0, 0));
	EXPECT_FALSE(e1.isDegenerated());
}

TEST(HalfEdgeTest, TestToDegenerate)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e1(&n1, &n2, 0);
	EXPECT_FALSE(e1.isDegenerated());
	e1.toDenerate();
	EXPECT_TRUE( e1.isDegenerated());
}

TEST(HalfEdgeTest, TestReverse)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e1(&n1, &n2, 0);
	e1.reverse();
	EXPECT_EQ( &n2, e1.getStart() );
	EXPECT_EQ( &n1, e1.getEnd() );
}

#include "../Core/Edge.h"

TEST(HalfEdgeTest, TestSplit)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	HalfEdge e1(&n1, &n3, 0);
	HalfEdge e2(&n3, &n1, 1);
	e1.setPair(&e2);
	//const HalfEdge e2(&n2, &n1, 0);
	//const HalfEdge e3(&n3, &n1, 0);
	HalfEdge* e3 = e1.split(&n2);
	EXPECT_EQ(&n1, e1.getStart());
	EXPECT_EQ(&n2, e1.getEnd());
	EXPECT_EQ(&n2, e3->getStart());
	EXPECT_EQ(&n3, e3->getEnd());
	delete e3;
}

TEST(HalfEdgeTest, TestGetHashKey)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	HalfEdge e1(&n1, &n2, 0);
	HalfEdge e2(&n2, &n1, 1);
	HalfEdge e3(&n1, &n3, 2);
	HalfEdge e4(&n3, &n1, 3);

	EXPECT_EQ(65536, e1.getHashKey());
	EXPECT_EQ(65536, e2.getHashKey());
	EXPECT_EQ(131072, e3.getHashKey());
	EXPECT_EQ(131072, e4.getHashKey());

}