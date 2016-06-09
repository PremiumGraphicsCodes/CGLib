#include "gtest\gtest.h"

#include "../Math/Quad.h"

using namespace Crystal::Math;

TEST(QuadTest, TestConstruct)
{
	const Quad<float> q(Vector3d<float>(0,0,0), Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	EXPECT_EQ( Vector3d<float>(0,0,0), q.getPosition(0,0) );
	EXPECT_EQ( Vector3d<float>(1,0,0), q.getPosition(1,0) );
	EXPECT_EQ( Vector3d<float>(0,1,0), q.getPosition(0,1) );
	EXPECT_EQ( Vector3d<float>(1,1,0), q.getPosition(1,1) );
}

TEST(QuadTest, TestPlaneXY)
{
	const Quad<float> q = Quad<float>::XYPlane(Vector3d<float>(0,0,0));
	EXPECT_EQ(Vector3d<float>(0, 0, 0), q.getPosition(0, 0));
	EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getPosition(1, 0));
	EXPECT_EQ(Vector3d<float>(0, 1, 0), q.getPosition(0, 1));
	EXPECT_EQ(Vector3d<float>(1, 1, 0), q.getPosition(1, 1));
	EXPECT_EQ(Vector3d<float>(0, 0, 1), q.getNormal());
}

TEST(QuadTest, TestPlaneYZ)
{
	const Quad<float> q = Quad<float>::YZPlane(Vector3d<float>(0, 0, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 0), q.getPosition(0, 0));
	EXPECT_EQ(Vector3d<float>(0, 1, 0), q.getPosition(1, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 1), q.getPosition(0, 1));
	EXPECT_EQ(Vector3d<float>(0, 1, 1), q.getPosition(1, 1));
	EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getNormal());
}

TEST(QuadTest, TestPlaneZX)
{
	const Quad<float> q = Quad<float>::ZXPlane(Vector3d<float>(0, 0, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 0), q.getPosition(0, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 1), q.getPosition(1, 0));
	EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getPosition(0, 1));
	EXPECT_EQ(Vector3d<float>(1, 0, 1), q.getPosition(1, 1));
	EXPECT_EQ(Vector3d<float>(0, 1, 0), q.getNormal());
}