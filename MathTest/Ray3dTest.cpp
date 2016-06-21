#include "gtest\gtest.h"
#include "../Math/Ray3d.h"
#include "../Math/Triangle3d.h"

using namespace Crystal::Math;

TEST(Ray3dTest, TestIsParallel)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangleYZ(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1), Vector3d<float>(0, 1, 1));
	EXPECT_TRUE(ray.isParallel(triangleYZ));
	Triangle3d<float> triangleXZ(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(1, 0, 1));
	EXPECT_TRUE(ray.isParallel(triangleXZ));
	Triangle3d<float> triangleXY(Vector3d<float>(-1, 0, 10), Vector3d<float>(1, 0, 10), Vector3d<float>(1, 1, 10));
	EXPECT_FALSE(ray.isParallel(triangleXY));

}

TEST(Ray3dTest, TestGetParamU)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangle(Vector3d<float>(-10, -10, 10), Vector3d<float>(-10, 10, 10), Vector3d<float>(10, 10, 10));
	EXPECT_EQ(0, ray.getParamU(triangle));
}


TEST(Ray3dTest, TestGetParam)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangle(Vector3d<float>(-10, -10, 10), Vector3d<float>(-10, 10, 10), Vector3d<float>(10, 10, 10));
	const auto& actual = ray.getParam(triangle);
}

TEST(Ray3dTest, TestHasIntersection)
{
	const Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangleYZ(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1), Vector3d<float>(0, 1, 1));
	EXPECT_FALSE(ray.hasIntersection(triangleYZ));
	Triangle3d<float> triangleXZ(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(1, 0, 1));
	EXPECT_FALSE(ray.hasIntersection(triangleXZ));
	Triangle3d<float> triangleXY(Vector3d<float>(-1, 0, 10), Vector3d<float>(1, 0, 10), Vector3d<float>(1, 1, 10));
	EXPECT_TRUE(ray.hasIntersection(triangleXY));

}


TEST(Ray3dTest, TestGetIntersection)
{
	Ray3d<float> ray(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));
	Triangle3d<float> triangle(Vector3d<float>(-10, -10, 10), Vector3d<float>(-10, 10, 10), Vector3d<float>(10, 10, 10));
	EXPECT_EQ(Vector3d<float>(0, 0, 10), ray.getIntersection(triangle));
}