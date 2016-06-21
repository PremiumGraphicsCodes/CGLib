#include "stdafx.h"

#include "../Core/Node.h"
#include "../Core/Edge.h"
#include "../Core/Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceTest, Test)
{
	Node n1(Vector3d<float>(0,0,0),0);
	Node n2(Vector3d<float>(1,0,0),0);
	Node n3(Vector3d<float>(1,1,0),0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f({ &e1, &e2, &e3 }, 0);
	EXPECT_EQ(Vector3d <float>(0, 0,1), f.getNormal() );
	EXPECT_EQ(0.5f, f.getArea());
}

TEST(FaceTest, TestGetIntersection)
{
	Node n1(Vector3d<float>(0, 0, 0), 0);
	Node n2(Vector3d<float>(1, 0, 0), 0);
	Node n3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f({ &e1, &e2, &e3 }, 0);
	const Ray3d<float> ray1(Vector3d<float>(0, 0, -10), Vector3d<float>(0, 0,1));
	EXPECT_TRUE(f.hasIntersection(ray1));
	EXPECT_EQ(Vector3d<float>(0, 0,0 ),f.getIntersection(ray1));
	const Ray3d<float> ray2(Vector3d<float>(2, 0, -10), Vector3d<float>(0, 0, 1));
	EXPECT_FALSE(f.hasIntersection(ray2));

}