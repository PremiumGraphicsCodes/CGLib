#include "gtest/gtest.h"

#include "../Math/Box2d.h"

using namespace Crystal::Math;

template<class T>
class Box2dTest : public testing::Test {
};

using TestTypes = ::testing::Types<float, double>;

TYPED_TEST_CASE(Box2dTest, TestTypes);

TYPED_TEST(Box2dTest, TestToArray)
{
	using T = TypeParam;
	Box2d<T> box(Vector2d<T>(-20, -10), Vector2d<T>(10, 20));
	const auto& actual = box.toArray();
	const std::array<T, 8> expected{ -20, 20, -20, -10, 10, -10, 10, 20 };
	EXPECT_EQ(expected, actual);
}
