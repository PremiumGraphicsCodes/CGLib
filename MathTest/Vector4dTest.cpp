#include "gtest/gtest.h"

#include "../Math/Vector4d.h"
#include "../Math/Matrix4d.h"

using namespace Crystal::Math;

TEST(Vector4dTest, TestGetDistanceSquared)
{
	Vector4d<float> v1(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4d<float> v2(2.0f, 2.0f, 3.0f, 1.0f);
	const auto actual = v1.getDistanceSquared(v2);
	EXPECT_EQ(1.0f, actual);
}

TEST(Vector4dTest, TestMultiple)
{
	Vector4d<float> v(1.0f, 2.0f, 3.0f, 1.0f);
	Matrix4d<float> m(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
	v.multiple(m);
	Vector4d<float> expected(2.0f, 3.0f, 4.0f, 1.0f);
	EXPECT_EQ( expected, v );
}