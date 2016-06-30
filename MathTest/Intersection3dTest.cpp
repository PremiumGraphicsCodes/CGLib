#include "gtest\gtest.h"
#include "../Math/Intersection3d.h"

using namespace Crystal::Math;

TEST(Intersection3dTest, TestLineTriangle)
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