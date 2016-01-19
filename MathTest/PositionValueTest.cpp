#include "gtest/gtest.h"

#include "../Math/PositionValue.h"

using namespace Crystal::Math;

template<class T>
class PositionValueTest : public testing::Test {
};

using TestTypes = ::testing::Types <
	std::tuple< float, float >//,
//	std::tuple< float, unsigned char >
>;

TYPED_TEST_CASE(PositionValueTest, TestTypes);

TYPED_TEST(PositionValueTest, TestInterpolate)
{
	using GeomType = std::tuple_element<0, TypeParam>::type;
	using ValueType = std::tuple_element<1, TypeParam>::type;

	PositionValue<GeomType, ValueType> pv1(Vector3d<GeomType>(0, 0, 0), 0);
	PositionValue<GeomType, ValueType> pv2(Vector3d<GeomType>(2, 4, 6), 10);
	const auto& actual = pv1.getInterpolatedPosition(5, pv2);
	const Vector3d<GeomType> expected(1, 2, 3);
	EXPECT_EQ(expected, actual);
}
