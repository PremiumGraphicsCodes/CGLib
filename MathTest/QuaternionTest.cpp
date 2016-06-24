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
	{
		const Quaternion<float> q1(0, 0, 0, 1);
		const Quaternion<float> q2(1, 1, 1, 1);
		const auto actual = q1.mult(q2);
		EXPECT_EQ(Quaternion<float>(1, 1, 1, 1), actual);
	}

	{
		Quaternion<float> q1(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
		Quaternion<float> q2(Vector3d<float>(0, 1, 0), Tolerance<float>::getHalfPI());
		auto q3 = q1 * q2;
		const auto& expected = q3.toMatrix();
		const auto& actual = Matrix3d<float>::RotateX(Tolerance<float>::getHalfPI()) * Matrix3d<float>::RotateY(Tolerance<float>::getHalfPI());
		EXPECT_EQ(expected, actual);
	}

	{
		Quaternion<float> q1(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
		Quaternion<float> q2(Vector3d<float>(0, 0, 1), Tolerance<float>::getHalfPI());
		auto q3 = q1 * q2;
		const auto& expected = q3.toMatrix();
		const auto& actual = Matrix3d<float>::RotateX(Tolerance<float>::getHalfPI()) * Matrix3d<float>::RotateZ(Tolerance<float>::getHalfPI());
		EXPECT_EQ(expected, actual);
	}

	{
		Quaternion<float> q1(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
		Quaternion<float> q2(Vector3d<float>(0, 1, 0), Tolerance<float>::getHalfPI());
		Quaternion<float> q3(Vector3d<float>(0, 0, 1), Tolerance<float>::getHalfPI());
		auto q4 = q1 * q2 * q3;
		const auto& expected = q4.toMatrix();
		const auto& actual = Matrix3d<float>::RotateX(Tolerance<float>::getHalfPI()) * Matrix3d<float>::RotateY(Tolerance<float>::getHalfPI()) * Matrix3d<float>::RotateZ(Tolerance<float>::getHalfPI());
		EXPECT_EQ(expected, actual);
	}

}

TEST(QuaternionTest, TestToMatrix)
{
	const Quaternion<float> q(0, 0, 0, 1);
	const auto& actual = q.toMatrix();
	EXPECT_EQ(Matrix3d<float>::Identity(), actual);
}

TEST(QuaternionTest, TestSlerp)
{
	{
		Quaternion<float> q1(Vector3d<float>(1, 0, 0), 0);
		Quaternion<float> q2(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
		const auto actual = q1.slerp(q2, 0.5);
		Quaternion<float> expected(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI()*0.5);
		EXPECT_EQ(expected, actual);
	}
	{
		Quaternion<float> q2(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
		Quaternion<float> q3(Vector3d<float>(1, 0, 0), Tolerance<float>::getPI());
		const auto actual = q2.slerp(q3, 0.5);
		Quaternion<float> expected(Vector3d<float>(1, 0, 0), Tolerance<float>::getPI()*0.75);
		EXPECT_EQ(expected, actual);
	}

	/*
	{
		Quaternion<float> q1(Vector3d<float>(1, 0, 0), Tolerance<float>::getPI());
		Quaternion<float> q2(Vector3d<float>(0, 1, 0), Tolerance<float>::getPI());
		const auto actual = q1.slerp(q2, 0.5);
		Quaternion<float> q3(Vector3d<float>(0, 0, 1), 0);

	}
	*/

}
