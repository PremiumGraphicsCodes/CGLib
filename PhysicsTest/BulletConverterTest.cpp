#include "gtest/gtest.h"

#include "../Physics/BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletConverterTest, TestConvertVector)
{
	const Vector3d<float> v(1, 2, 3);
	const auto actual = BulletConverter::convert(v);
	EXPECT_EQ(1, actual.getX());
	EXPECT_EQ(2, actual.getY());
	EXPECT_EQ(3, actual.getZ());
}

TEST(BulletConverterTest, TestConvertVector2)
{
	const btVector3 src(1, 2, 3);
	const auto actual = BulletConverter::convert(src);
	EXPECT_EQ(1, actual.getX());
	EXPECT_EQ(2, actual.getY());
	EXPECT_EQ(3, actual.getZ());
}

TEST(BulletConverterTest, TestConvertTransform)
{
	btMatrix3x3 matrix(1, 0, 0, 0, 1, 0, 0, 0, 1);
	btVector3 vector(1, 1, 1);
	btTransform transform(matrix, vector);
	const auto actual = BulletConverter::convert(transform);
	const Matrix4d<float> expected(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 1);
	EXPECT_EQ(expected, actual);
}