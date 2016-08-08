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