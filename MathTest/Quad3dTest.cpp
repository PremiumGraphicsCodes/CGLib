#include "gtest\gtest.h"

#include "../Math/Quad3d.h"
#include "../Math/Point3d.h"

using namespace Crystal::Math;

TEST(Quad3dTest, TestGetArea)
{
	const Quad3d<float> q1(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const Quad3d<float> q2(Vector3d<float>(0, 0, 0), Vector3d<float>(-1, 0, 0), Vector3d<float>(0, 1, 0));

	EXPECT_EQ(1, q1.getArea());
	EXPECT_EQ(1, q2.getArea());
}

TEST(Quad3dTest, TestGetPosition)
{
	const Quad3d<float> q1(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 0), q1.getPosition(0, 0));
	EXPECT_EQ(Vector3d<float>(1, 0, 0), q1.getPosition(1, 0));
	EXPECT_EQ(Vector3d<float>(0, 1, 0), q1.getPosition(0, 1));
	EXPECT_EQ(Vector3d<float>(1, 1, 0), q1.getPosition(1, 1));

	const Quad3d<float> q2(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 0, 0), Vector3d<float>(0, 1, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 0), q2.getPosition(0, 0));
	EXPECT_EQ(Vector3d<float>(2, 0, 0), q2.getPosition(1, 0));
	EXPECT_EQ(Vector3d<float>(0, 1, 0), q2.getPosition(0, 1));
	EXPECT_EQ(Vector3d<float>(2, 1, 0), q2.getPosition(1, 1));
}

TEST(Quad3dTest, TestPlaneXY)
{
	const auto actual = Quad3d<float>::XYPlane(Vector3d<float>(0,0,0));
	const auto expected = Quad3d<float>(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	EXPECT_EQ( expected, actual );
}

TEST(Quad3dTest, TestPlaneYZ)
{
	const Quad3d<float> actual = Quad3d<float>::YZPlane(Vector3d<float>(0, 0, 0));
	const Quad3d<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 1, 0), Vector3d<float>(0, 0, 1));
	EXPECT_EQ(expected, actual);
}

TEST(Quad3dTest, TestPlaneZX)
{
	const Quad3d<float> actual = Quad3d<float>::ZXPlane(Vector3d<float>(0, 0, 0));
	const Quad3d<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1), Vector3d<float>(1, 0, 0));
	EXPECT_EQ(expected, actual);
}

TEST(Quad3dTest, TestGetNormal)
{
	const Quad3d<float> q1 = Quad3d<float>::XYPlane(Vector3d<float>(0, 0, 0));
	EXPECT_EQ(Vector3d<float>(0, 0, 1), q1.getNormal());

	const Quad3d<float> q2 = Quad3d<float>::YZPlane(Vector3d<float>(0, 0, 0));
	EXPECT_EQ(Vector3d<float>(1, 0, 0), q2.getNormal());

	const Quad3d<float> q3 = Quad3d<float>(Vector3d<float>(1, 0, 0), Vector3d<float>(0, 0, 1), Vector3d<float>(0, 1, 0));
	EXPECT_EQ(Vector3d<float>(-1, 0, 0), q3.getNormal());
}

TEST(Quad3dTest, TestGetPoint)
{
	const Quad3d<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	const Point3d<float> expected1(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1), Vector2d<float>(0, 0));
	const Point3d<float> expected2(Vector3d<float>(1, 0, 0), Vector3d<float>(0, 0, 1), Vector2d<float>(1, 0));
	const Point3d<float> expected3(Vector3d<float>(0, 1, 0), Vector3d<float>(0, 0, 1), Vector2d<float>(0, 1));
	const Point3d<float> expected4(Vector3d<float>(1, 1, 0), Vector3d<float>(0, 0, 1), Vector2d<float>(1, 1));

	EXPECT_EQ(expected1, q.getPoint(0, 0));
	EXPECT_EQ(expected2, q.getPoint(1, 0));
	EXPECT_EQ(expected3, q.getPoint(0, 1));
	EXPECT_EQ(expected4, q.getPoint(1, 1));
}