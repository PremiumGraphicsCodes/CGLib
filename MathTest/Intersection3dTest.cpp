#include "gtest\gtest.h"
#include "../Math/Intersection3d.h"

using namespace Crystal::Math;


TEST(Intersection3d, TestLineAndLine)
{
	using T = float;
	Line3d<T> linex(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0));
	Line3d<T> liney(Vector3d<T>(0, -1, 0), Vector3d<T>(0, 1, 0));
	Line3d<T> linez(Vector3d<T>(0, 0, -1), Vector3d<T>(0, 0, 1));
	Line3d<T> linexy(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 0));
	Line3d<T> linex2(Vector3d<T>(2, 0, 0), Vector3d<T>(4, 0, 0));


	EXPECT_EQ(Vector3d<T>(0, 0, 0), Intersection3d<T>(linex, liney).getIntersections().front() );
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Intersection3d<T>(linex, linez).getIntersections().front());
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Intersection3d<T>(linex, linexy).getIntersections().front());
	EXPECT_FALSE(Intersection3d<T>(linex, linex2).hasIntersection());


	{
		Line3d<T> line1(Vector3d<T>(0, 1, 0), Vector3d<T>(-1, 0, 0));
		Line3d<T> line2(Vector3d<T>(0, 0, 0), Vector3d<T>( 2, 0, 0));
		Intersection3d<T> i(line1, line2);
		EXPECT_TRUE( i.getIntersections().empty() );
	}
	//EXPECT_EQ(Vector3d<T>(1, 0, 0), linex.getIntersection(Line3d<T>(Vector3d<T>(1, -1, 0), Vector3d<T>(1, 1, 0))));

	//EXPECT_EQ(actual, 1.0);
}


TEST(Intersection3dTest, TestLineAndTriangle)
{
	using T = float;
	Triangle3d<T> triangle(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	{
		Line3d<T> line(Vector3d<T>(0, 0, -1), Vector3d<T>(0, 0, 1));
		Intersection3d<T> intersection(line, triangle);
		EXPECT_TRUE(intersection.hasIntersection());
		EXPECT_EQ(Vector3d<T>(0, 0, 0), intersection.getIntersections().front());
	}
	{
		Line3d<T> line(Vector3d<T>(2, 0, -1), Vector3d<T>(2, 0, 1));
		Intersection3d<T> intersection(line, triangle);
		EXPECT_FALSE(intersection.hasIntersection());
	}
}

TEST(Intersection3dTest, TestTriangleAndTriangle)
{
	using T = float;
	Triangle3d<T> t1(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	Triangle3d<T> t2(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 0, 0), Vector3d<T>(1, 2, 0));
	Intersection3d<T> intersection(t1, t2);
	EXPECT_EQ(2, intersection.getIntersections().size());
}