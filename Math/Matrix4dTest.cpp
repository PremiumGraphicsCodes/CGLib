#include "gtest/gtest.h"

#include "Matrix4d.h"

using namespace Crystal::Math;

template<class T>
class Matrix4dTest : public testing::Test {
};

typedef ::testing::Types<double> TestTypes;

TYPED_TEST_CASE(Matrix4dTest, TestTypes);

TYPED_TEST(Matrix4dTest, ContructTest)
{
	using T = TypeParam;
	Matrix4d<T> m;
	EXPECT_EQ(Matrix4d<T>::Identity(), m);
}

TYPED_TEST(Matrix4dTest, RotateYTest)
{
	using T = TypeParam;
	EXPECT_EQ(Matrix4d<T>::Identity(), Matrix4d<T>::RotateX(0.0f));
	EXPECT_EQ(Matrix4d<T>::Identity(), Matrix4d<T>::RotateY(0.0f));
	EXPECT_EQ(Matrix4d<T>::Identity(), Matrix4d<T>::RotateZ(0.0f));
}

TYPED_TEST(Matrix4dTest, toArraysTest)
{
	using T = TypeParam;

	const Matrix4d<T>& m = Matrix4d<T>::Identity();
	const auto& x = m.toArray();
	EXPECT_EQ(x[0], 1.0f);
	EXPECT_EQ(x[1], 0.0f);
	EXPECT_EQ(x[2], 0.0f);
	EXPECT_EQ(x[3], 0.0f);
}

TYPED_TEST(Matrix4dTest, TestEquals)
{
	using T = TypeParam;

	EXPECT_NE(Matrix4d<T>::Zero(), Matrix4d<T>::Identity());
}