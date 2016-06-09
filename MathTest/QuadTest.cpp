#include "gtest\gtest.h"

#include "../Math/Quad.h"

using namespace Crystal::Math;

TEST(QuadTest, TestGetPosition)
{
	{
		const Quad<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
		EXPECT_EQ(Vector3d<float>(0, 0, 0), q.getPosition(0, 0));
		EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getPosition(1, 0));
		EXPECT_EQ(Vector3d<float>(0, 1, 0), q.getPosition(0, 1));
		EXPECT_EQ(Vector3d<float>(1, 1, 0), q.getPosition(1, 1));
	}
	{
		const Quad<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 0, 0), Vector3d<float>(0, 1, 0));
		EXPECT_EQ(Vector3d<float>(0, 0, 0), q.getPosition(0, 0));
		EXPECT_EQ(Vector3d<float>(2, 0, 0), q.getPosition(1, 0));
		EXPECT_EQ(Vector3d<float>(0, 1, 0), q.getPosition(0, 1));
		EXPECT_EQ(Vector3d<float>(2, 1, 0), q.getPosition(1, 1));
	}
}

TEST(QuadTest, TestPlaneXY)
{
	const Quad<float> actual = Quad<float>::XYPlane(Vector3d<float>(0,0,0));
	const Quad<float> expected = Quad<float>(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	EXPECT_EQ( expected, actual );
}

TEST(QuadTest, TestPlaneYZ)
{
	const Quad<float> actual = Quad<float>::YZPlane(Vector3d<float>(0, 0, 0));
	const Quad<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 1, 0), Vector3d<float>(0, 0, 1));
	EXPECT_EQ(expected, actual);
}

TEST(QuadTest, TestPlaneZX)
{
	const Quad<float> actual = Quad<float>::ZXPlane(Vector3d<float>(0, 0, 0));
	const Quad<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1), Vector3d<float>(1, 0, 0));
	EXPECT_EQ(expected, actual);
}

TEST(QuadTest, TestGetNormal)
{
	{
		const Quad<float> q = Quad<float>::XYPlane(Vector3d<float>(0, 0, 0));
		EXPECT_EQ(Vector3d<float>(0, 0, 1), q.getNormal());
	}

	{
		const Quad<float> q = Quad<float>::YZPlane(Vector3d<float>(0, 0, 0));
		EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getNormal());

	}
	//EXPECT_EQ(Vector3d<float>(1, 0, 0), q.getPosition(1, 0));
}