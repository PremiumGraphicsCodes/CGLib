#include "stdafx.h"
#include "../Core/Vertex.h"
#include "../Core/HalfEdge.h"
#include "../Core/Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeTest, TestBuild)
{
	Edge e;
	Vertex v1(Vector3d<float>(0,0,0));
	Vertex v2(Vector3d<float>(1,0,0));
	auto actual = e.build(&v1, &v2);
	EXPECT_EQ( &v1, actual.getLeft()->getStart());
	EXPECT_EQ( &v2, actual.getLeft()->getEnd());
	EXPECT_EQ( &v2, actual.getRight()->getStart());
	EXPECT_EQ( &v1, actual.getRight()->getEnd());
}

TEST(EdgeTest, TestConnect)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(2, 0, 0));

	HalfEdge hf1(&v1, &v2, 0);
	HalfEdge hf2(&v2, &v1, 1);

	Edge e1(&hf1, &hf2);

	HalfEdge hf3(&v2, &v3, 2);
	HalfEdge hf4(&v3, &v2, 3);

	Edge e2(&hf3, &hf4);

	e1.connect(e2);
	EXPECT_EQ(nullptr, e1.getRight()->getNext());

	EXPECT_EQ(&hf3, e1.getLeft()->getNext());
	EXPECT_EQ(&hf2, e2.getRight()->getNext());

	//EXPECT_EQ(&hf1, e2.getRight()->getNext());

}


TEST(EdgeTest, TestCreateEdges)
{
	Edge e;
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(2, 0, 0));

	auto actual = e.createEdges({ &v1, &v2,&v3 });
	EXPECT_EQ(&v1, actual[0].getLeft()->getStart());
	EXPECT_EQ(&v2, actual[0].getLeft()->getEnd());
	EXPECT_EQ(actual[1].getLeft(), actual[0].getLeft()->getNext());
}


TEST(EdgeTest, TestSplit)
{
	Edge e;
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(2, 0, 0));
	auto e2 = e.build(&v1, &v3);
	auto actual = e2.split(&v2);
	EXPECT_EQ(&v1, actual[0].getLeft()->getStart());
	EXPECT_EQ(&v2, actual[0].getLeft()->getEnd());
	EXPECT_EQ(&v2, actual[1].getLeft()->getStart());
	EXPECT_EQ(&v3, actual[1].getLeft()->getEnd());
	//EXPECT_EQ(actual[1].getLeft(), actual[0].getLeft()->getNext());

	EXPECT_EQ(&v3, actual[1].getRight()->getStart());
	EXPECT_EQ(&v2, actual[1].getRight()->getEnd());
	EXPECT_EQ(&v2, actual[0].getRight()->getStart());
	EXPECT_EQ(&v1, actual[0].getRight()->getEnd());

}