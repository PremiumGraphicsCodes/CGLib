#include "gtest/gtest.h"
 
#include "../Math/Quaternion.h"

using namespace Crystal::Math;

 
TEST( QuaternionTest, TestConstruct )
{
	Quaternion<float> q;
}

TEST(QuaternionTest, TestGetConjugate)
{
	const Quaternion<float> q(1,2,3,1);
	const Quaternion<float> expected(-1, -2, -3, 1);
	EXPECT_EQ( expected, q.getConjugate() );
}

TEST(QuaternionTest, TestGetInverse)
{
	{
		const Quaternion<float> q(0, 0, 0, 1);
		const auto actual = q.getInverse();
		const Quaternion<float> expected(0, 0, 0, 1);
		EXPECT_EQ(expected, actual);
	}

	{
		const Quaternion<float> q(1, 2, 3, 1);
		const auto actual = q.getInverse();
		//const Quaternion<float> expected(0, 0, 0, 1);
		auto m = q.mult(actual);
		EXPECT_EQ(m, Quaternion<float>());
		//expected
		//EXPECT_EQ(expected, actual);
	}
}

TEST(QuaternionTest, TestMult)
{
	const Quaternion<float> q1(0, 0, 0, 1);
	const Quaternion<float> q2(1, 1, 1, 1);
	const auto actual = q1.mult(q2);
}
