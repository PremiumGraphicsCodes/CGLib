#include "stdafx.h"
#include "../Core/Face.h"
#include "../Core/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceTest, TestGetArea)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 0);
	Vertex v3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&v1, &v2);
	Edge e2(&v2, &v3);
	Edge e3(&v3, &v1);

	Face f(&e1, &e2, &e3);
	EXPECT_FLOAT_EQ(1, f.getArea());
	v3.moveTo(Vector3d<float>(1, -2, 0));
	EXPECT_FLOAT_EQ(2, f.getArea());
}

TEST(FaceTest, TestGetOrientation)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 0);
	Vertex v3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&v1, &v2);
	Edge e2(&v2, &v3);
	Edge e3(&v3, &v1);

	Face f(&e1, &e2, &e3);
	EXPECT_EQ( Orientation::CCW, f.getOrientation(Vector3d<float>(0, 0, 1)) );
	EXPECT_EQ( Orientation::CW, f.getOrientation(Vector3d<float>(0, 0, -1)));

	v3.moveTo(Vector3d<float>(1, -2, 0));
	EXPECT_EQ(Orientation::CW, f.getOrientation(Vector3d<float>(0, 0, 1)));
	EXPECT_EQ(Orientation::CCW, f.getOrientation(Vector3d<float>(0, 0, -1)));

	EXPECT_EQ(Orientation::None, f.getOrientation(Vector3d<float>(1, 1, 0)));

}

TEST(FaceTest, TestToDegenerate)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 0);
	Vertex v3(Vector3d<float>(1, 1, 0), 0);

	Edge e1(&v1, &v2);
	Edge e2(&v2, &v3);
	Edge e3(&v3, &v1);

	Face f(&e1, &e2, &e3);
	EXPECT_FALSE(f.isDegenerated());
	f.toDegenerate();
	EXPECT_TRUE( f.isDegenerated());
}