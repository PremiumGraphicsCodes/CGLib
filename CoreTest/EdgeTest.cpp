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