#include "gtest/gtest.h"

#include "../Math/Vector.h"

using namespace Crystal::Math;

TEST(VectorTest, TestGetInnerProduct)
{
	Vector<3, double> v1({ 1,0,1 });
	Vector<3, double> v2({ 1,1,1 });
	EXPECT_EQ( 2, v1.getInnerProduct(v2) );
}