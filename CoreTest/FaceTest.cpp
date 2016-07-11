#include "stdafx.h"

#include "../Core/Vertex.h"
#include "../Core/Edge.h"
#include "../Core/Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceTest, TestGetArea)
{
	Vertex n1(Vector3d<float>(0,0,0),0);
	Vertex n2(Vector3d<float>(1,0,0),0);
	Vertex n3(Vector3d<float>(1,1,0),0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f1({ &e1, &e2, &e3 }, 0);
	EXPECT_EQ(0.5f, f1.getArea());
	//Face f2({ &e1, &e3, &e2 }, 0);
	//EXPECT_EQ(-0.5f, f2.getArea());

}

TEST(FaceTest, TestGetNormal)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 0);
	Vertex n3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f({ &e1, &e2, &e3 }, 0);
	EXPECT_EQ(Vector3d<float>(0, 0, 1), f.getNormal());
}

TEST(FaceTest, TestIsCCW)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 0);
	Vertex n3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f1({ &e1, &e2, &e3 }, 0);
	EXPECT_TRUE(f1.isCCW());
	//Face f2({ &e1, &e3, &e2 }, 0);
	//EXPECT_TRUE(f2.isCW());

}



TEST(FaceTest, TestGetIntersection)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 0);
	Vertex n3(Vector3d<float>(1, 1, 0), 0);

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

TEST(FaceTest, TestIsCollapsed)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 0);
	Vertex n3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&n1, &n2, 0);
	Edge e2(&n2, &n3, 1);
	Edge e3(&n3, &n1, 2);

	Face f1({ &e1, &e2, &e3 }, 0);
	EXPECT_FALSE(f1.isCollapsed());
	Face f2({ &e1, &e2, nullptr }, 1);
	EXPECT_TRUE( f2.isCollapsed());
}