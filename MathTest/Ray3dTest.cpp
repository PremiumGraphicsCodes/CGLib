#include "gtest\gtest.h"
#include "../Math/Ray3d.h"
#include "../Math/Triangle3d.h"

using namespace Crystal::Math;

TEST(Ray3dTest, TestGetParam)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangle(Vector3d<float>(-10, -10, 10), Vector3d<float>(-10, 10, 10), Vector3d<float>(10, 10, 10));
	const auto& actual = ray.getParam(triangle);
}

TEST(Ray3dTest, TestGetIntersection)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangle(Vector3d<float>(-10, -10, 10), Vector3d<float>(-10, 10, 10), Vector3d<float>(10, 10, 10));
	EXPECT_EQ(Vector3d<float>(0, 0, 10), ray.getIntersection(triangle));
}