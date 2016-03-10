#include "gtest/gtest.h"

#include "../Physics/BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletConverterTest, TestConvertVector)
{
	BulletConverter converter;
	const Vector3d<float> v(1, 2, 3);
	const auto actual = converter.convert(v);
	EXPECT_EQ(1, actual.getX());
	EXPECT_EQ(2, actual.getY());
	EXPECT_EQ(3, actual.getZ());
}

TEST(BulletConverterTest, TestConvertVector2)
{
	BulletConverter converter;
	const btVector3 src(1, 2, 3);
	const auto actual = converter.convert(src);
	EXPECT_EQ(1, actual.getX());
	EXPECT_EQ(2, actual.getY());
	EXPECT_EQ(3, actual.getZ());
}