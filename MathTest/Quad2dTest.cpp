#include "gtest/gtest.h"
#include "../Math/Quad2d.h"

using namespace Crystal::Math;

TEST(Quad2dTest, TestGetArea)
{
	const Quad2d<float> q1;
	const Quad2d<float> q2(Vector2d<float>(0, 0), Vector2d<float>(2, 4));

	EXPECT_EQ(1.0f, q1.getArea());
	EXPECT_EQ(8.0f, q2.getArea());
}

TEST(Quad2dTest, TestGetPosition)
{
	const Quad2d<float> q1;
	const Quad2d<float> q2(Vector2d<float>(0, 0), Vector2d<float>(2, 4));

	EXPECT_EQ(Vector2d<float>(0,0), q1.getPosition(0,0));
	EXPECT_EQ(Vector2d<float>(1,2), q2.getPosition(0.5, 0.5));
}


TEST(Quad2dTest, TestMoveStart)
{
	Quad2d<float> q1;
	//const Quad2d<float> q2(Vector2d<float>(0, 0), Vector2d<float>(2, 4));
	Quad2d<float> expected(Vector2d<float>(2, 0), Vector2d<float>(-1, 1));
	q1.moveStartTo(Vector2d<float>(2, 0));
	EXPECT_EQ(-1.0f, q1.getArea());
	EXPECT_EQ(Vector2d<float>(1, 1), q1.getEnd());

	EXPECT_EQ(expected, q1);
	//EXPECT_EQ(8.0f, q2.getArea());
}