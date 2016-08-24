#include "stdafx.h"

#include "../Core/HalfEdgeRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(HalfEdgeRepositoryTest, TestFindReverse)
{
	Vertex v1(Vector3d<float>(0,0,0));
	Vertex v2(Vector3d<float>(1,0,0));

	HalfEdge e1(&v1, &v2);
	HalfEdge e2(&v2, &v1);
	std::list<HalfEdge*> es = { &e1, &e2 };
	HalfEdgeRepository edges(es);
	EXPECT_EQ( &e2, edges.findReverse(&e1) );
}

TEST(HalfEdgeRepositoryTest, TestFindPair)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));

	HalfEdge e1(&v1, &v2);
	HalfEdge e2(&v2, &v1);
	std::list<HalfEdge*> es = { &e1, &e2 };
	HalfEdgeRepository edges(es);
	edges.setPairs();
	EXPECT_EQ(&e2, e1.getPair());
}