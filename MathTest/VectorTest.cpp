#include "gtest/gtest.h"

#include "../Math/Vector.h"

using namespace Crystal::Math;


template<class T>
class VectorTest : public testing::Test {
};


using TestTypes = ::testing::Types<float, double>;

TYPED_TEST_CASE(VectorTest, TestTypes);


TYPED_TEST(VectorTest, TestGetInnerProduct)
{
	Vector<3, TypeParam> v1({ 1,0,1 });
	Vector<3, TypeParam> v2({ 1,1,1 });
	EXPECT_EQ( 2, v1.getInnerProduct(v2) );
}