#include "gtest/gtest.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;

template<class T>
class Line3dTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(Line3dTest, TestTypes);

TYPED_TEST(Line3dTest, TestGet)
{
	using T = TypeParam;

	const Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	EXPECT_EQ( Vector3d<T>(0, 0, 0), line.getStart());
	EXPECT_EQ( Vector3d<T>(0.5, 2.5, 5), line.getCenter());
	EXPECT_EQ( Vector3d<T>(1, 5, 10), line.getEnd());
}

TYPED_TEST(Line3dTest, TestGetPosition)
{
	using T = TypeParam;
	const Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	EXPECT_EQ(Vector3d<T>(0,0,0), line.getPosition(0));
	EXPECT_EQ(Vector3d<T>(0.5, 2.5, 5), line.getPosition(0.5));

}

TYPED_TEST(Line3dTest, TestToPositions)
{
	using T = TypeParam;
	const Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	const auto& actual = line.toPositionsByNumber(2);
	EXPECT_EQ(2, actual.size());
}

TYPED_TEST(Line3dTest, TestMove)
{
	using T = TypeParam;
	Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	line.move(Vector3d<T>(2, 3, 4));
	EXPECT_EQ(Vector3d<T>(2, 3, 4), line.getStart());
	EXPECT_EQ(Vector3d<T>(3, 8, 14), line.getEnd());
}


TYPED_TEST(Line3dTest, TestMoveStartTo)
{
	using T = TypeParam;
	Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	line.moveStartTo(Vector3d<T>(3, 1, 2));
	EXPECT_EQ(Vector3d<T>(3, 1, 2), line.getStart());
	EXPECT_EQ(Vector3d<T>(1, 5, 10), line.getEnd());
}

TYPED_TEST(Line3dTest, TestMoveEndTo)
{
	using T = TypeParam;
	Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 5, 10));
	line.moveEndTo(Vector3d<T>(3, 1, 2));
	EXPECT_EQ(Vector3d<T>(0, 0, 0), line.getStart());
	EXPECT_EQ(Vector3d<T>(3, 1, 2), line.getEnd());

}

TYPED_TEST(Line3dTest, TestGetDistance)
{
	using T = TypeParam;
	Line3d<T> line(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 0, 0));
	const auto actual = line.getDistance(Vector3d<T>(0.5, 1.0, 0.0));
	EXPECT_EQ(actual, 1.0);
}

/*
TYPED_TEST(Line3dTest, TestHasIntersection)
{
	using T = TypeParam;
	Line3d<T> xline(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0));
	Line3d<T> yline(Vector3d<T>(0, -1, 0), Vector3d<T>(0, 1, 0));
	Line3d<T> zline(Vector3d<T>(0, 0, -1), Vector3d<T>(0, 0, 1));

	EXPECT_TRUE(xline.hasIntersection(yline));
	EXPECT_TRUE(yline.hasIntersection(xline));

	EXPECT_TRUE(xline.hasIntersection(zline));
	EXPECT_TRUE(zline.hasIntersection(yline));

	EXPECT_FALSE(xline.hasIntersection(Line3d<T>(Vector3d<T>(2, 0, 0), Vector3d<T>(4, 0, 0))));
}

TYPED_TEST(Line3dTest, TestGetDistanceByLine)
{
	using T = TypeParam;
	Line3d<T> xline(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0));
	Line3d<T> xline2(Vector3d<T>(2, 0, 0), Vector3d<T>(4, 2, 0));

	Line3d<T> yline(Vector3d<T>(0, -1, 0), Vector3d<T>(0, 1, 0));

	EXPECT_EQ(0, xline.getDistance(yline));
	EXPECT_EQ(1, xline.getDistance(xline2));

}
*/