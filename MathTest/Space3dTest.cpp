#include "gtest/gtest.h"

#include "../Math/Space3d.h"

using namespace Crystal::Math;


TEST(Space3dTest, TestGetStart)
{
	using T = float;
	EXPECT_EQ( Vector3d<T>(0,0,0), Space3d<T>().getStart());
	EXPECT_EQ( Vector3d<T>(1,1,1), Space3d<T>(Vector3d<T>(1,1,1)).getStart());
}

TEST(Space3dTest, TestGetCenter)
{
	using T = float;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Space3d<T>().getCenter());
	EXPECT_EQ(Vector3d<T>(5, 6, 7), Space3d<T>(Vector3d<T>(0,2,4), Vector3d<T>(10,8,6)).getCenter());

}

TEST(Space3dTest, TestGetEnd)
{
	using T = float;
	EXPECT_EQ( Vector3d<T>(0,0,0), Space3d<T>().getEnd());
	EXPECT_EQ( Vector3d<T>(10, 10, 10), Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(5, 5, 5)).getEnd() );
}

TEST(Space3dTest, TestGetVolume)
{
	using T = float;
	EXPECT_EQ(0, Space3d<T>().getVolume());
	EXPECT_EQ(125, Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(5, 5, 5)).getVolume());
}

TEST(Space3dTest, TestGetSubSpaces)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	{
		const auto& actual = s.getSubSpaces(2, 1, 1);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(5, 10, 10)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(5, 0, 0), Vector3d<T>(5, 10, 10)), actual[1]);
	}
	{
		const auto& actual = s.getSubSpaces(1, 2, 1);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 5, 10)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 5, 0), Vector3d<T>(10, 5, 10)), actual[1]);
	}
	{
		const auto actual = s.getSubSpaces(1, 1, 2);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 5)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 5), Vector3d<T>(10, 10, 5)), actual[1]);
	}

}


TEST(Space3dTest, TestGetDividedWithEdge)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	{
		const auto actual = s.getDividedWithEdge(1, 1, 1);
		EXPECT_EQ(27, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(-10, -10, -10), Vector3d<T>(10, 10, 10)), actual.front());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(10, 10, 10), Vector3d<T>(10, 10, 10)), actual.back());
	}

}

TEST(Space3dTest, TestHasIntersection)
{
	using T = float;
	{
		const auto lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
		const auto rhs = Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(10, 10, 10));
		EXPECT_TRUE(lhs.hasIntersection(rhs));
	}

	{
		const auto lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
		const auto rhs = Space3d<T>(Vector3d<T>(10, 10, 10), Vector3d<T>(10, 10, 10));
		EXPECT_FALSE(lhs.hasIntersection(rhs));
	}
}

TEST(Space3dTest, TestGetOveralpped)
{
	using T = float;
	{
		const auto lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
		const auto rhs = Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(10, 10, 10));
		EXPECT_EQ( Space3d<T>(Vector3d<T>(5,5,5), Vector3d<T>(5,5,5) ), lhs.getOverlapped(rhs) );
	}

	{
		const auto lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
		const auto rhs = Space3d<T>(Vector3d<T>(10, 10, 10), Vector3d<T>(10, 10, 10));
		EXPECT_EQ( Space3d<T>(), lhs.getOverlapped(rhs));
	}
}

TEST(Space3dTest, TestGetBoundingSpace)
{
	using T = float;
	{
		const auto& lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
		const auto& rhs = Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(10, 10, 10));
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(15, 15, 15)), lhs.getBoundingSpace(rhs));
	}
}

TEST(Space3dTest, TestToArray)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const std::array< Vector3d<T>, 8 >& actual = s.toArray();
	EXPECT_EQ(Vector3d<T>(0, 0, 0), actual[0]);
	EXPECT_EQ(Vector3d<T>(1, 0, 0), actual[1]);
	EXPECT_EQ(Vector3d<T>(1, 1, 0), actual[2]);
	EXPECT_EQ(Vector3d<T>(0, 1, 0), actual[3]);
	EXPECT_EQ(Vector3d<T>(0, 0, 1), actual[4]);
	EXPECT_EQ(Vector3d<T>(1, 0, 1), actual[5]);
	EXPECT_EQ(Vector3d<T>(1, 1, 1), actual[6]);
	EXPECT_EQ(Vector3d<T>(0, 1, 1), actual[7]);
}

TEST(Space3dTest, TestOffset)
{
	using T = float;
	const auto space = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	const auto actual = space.offset(Vector3d<T>(2, 2, 2));
	EXPECT_EQ(Vector3d<T>(1, 1, 1), actual.getStart());
	EXPECT_EQ(Vector3d<T>(9, 9, 9), actual.getEnd());
}

TEST(Space3dTest, TestMoveStart)
{
	using T = float;
	
	Space3d<T> space(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	space.moveStart(Vector3d<T>(1, 1, 1));

	EXPECT_EQ( Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(9, 9, 9)), space );
}

TEST(Space3dTest, TestMoveEnd)
{
	using T = float;

	Space3d<T> space(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	space.moveEnd(Vector3d<T>(-1, -1, -1));
	EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(9, 9, 9)), space);
}

TEST(Space3dTest, TestMove)
{
	using T = float;

	Space3d<T> s0(Vector3d<T>(1, 1, 1), Vector3d<T>(10, 10, 10));
	Space3d<T> s1(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	s1.move(Vector3d<T>(1, 1, 1));

	EXPECT_EQ(s0, s1);
}

TEST(Space3dTest, TestScale)
{
	using T = float;

	Space3d<T> s(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	s.scale(Vector3d<T>(1, 2, 4));
}

TEST(Space3dTest, TestGetSubSpace)
{
	using T = float;

	const auto space = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	{
		const auto i = Index3d{ 0, 0, 0 };
		const auto& actual = space.getSubSpace(i, 10, 10, 10);
		const auto expected = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
		EXPECT_EQ(expected, actual);
	}

	{
		const auto i = Index3d{9, 9, 9};

		const auto& actual = space.getSubSpace(i, 10, 10, 10);
		const auto expected = Space3d<T>(Vector3d<T>(9,9,9), Vector3d<T>(1, 1, 1));
		EXPECT_EQ(expected, actual);

	}
}

TEST(Space3dTest, TestGetPowerOfTwo)
{
	Space3d<float> space(Vector3d<float>(-1.5, -3, -4), Vector3d<float>(3, 6, 8));
	EXPECT_EQ(Vector3d<float>(2, 4, 8), space.getPowerOfTwo());
}

TEST(Space3dTest, TestCreatePowerOfTwoSpace)
{
	Space3d<float> space(Vector3d<float>(-1.5, -3, -4), Vector3d<float>(3, 6, 8));
	Space3d<float> expected(Vector3d<float>(-2, -4, -8), Vector3d<float>(4, 8, 16));
	Space3d<float> actual = space.createPowerOfTwoSpace();
	EXPECT_EQ(expected, actual);
}

/*

TEST(Space3dTest, TestEquals)
{
	using T = float;
	EXPECT_EQ(Space1d<T>(), Space1d<T>());
	EXPECT_NE(Space1d<T>(), Space1d<T>(Position1d<T>({ 1 })));

}
*/