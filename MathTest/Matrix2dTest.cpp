#include "gtest/gtest.h"
 
#include "../Math/Matrix2d.h"

using namespace Crystal::Math;

template<class T>
class Matrix2dTest : public testing::Test {
};

typedef ::testing::Types<double> TestTypes;

TYPED_TEST_CASE(Matrix2dTest, TestTypes);

TYPED_TEST(Matrix2dTest, TestConstruct)
{
	Matrix2d< TypeParam > m;
	EXPECT_EQ(Matrix2d<TypeParam>::Identity(), m);
}

TYPED_TEST(Matrix2dTest, TestRotate)
{
	using T = TypeParam;
	EXPECT_EQ(Matrix2d<T>::Identity(), Matrix2d<T>::Rotate(0.0));
	EXPECT_EQ(Matrix2d<T>(0, -1, 1, 0), Matrix2d<T>::Rotate(0.5 * Tolerance<T>::getPI()));
}

TYPED_TEST(Matrix2dTest, TestGetRotationAngle)
{
	using T = TypeParam;
	const Matrix2d<T> m(0, -1, 1, 0);
	m.isRotation();
	EXPECT_EQ(Angle<T>::HalfPI(), m.getRotationAngle());
}

TYPED_TEST(Matrix2dTest, TestDeterminent)
{
	EXPECT_EQ(1, Matrix2d<TypeParam>::Identity().getDeterminant());
	EXPECT_EQ(0, Matrix2d<TypeParam>::Zero().getDeterminant());
}

TYPED_TEST(Matrix2dTest, InverseTest)
{
	{
		Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		EXPECT_TRUE(m.hasInverse());
		const Matrix2d<TypeParam>& i = m.getInverse();
		EXPECT_EQ(Matrix2d<TypeParam>::Identity(), i);
	}

	{
		Matrix2d<TypeParam> m( 2, 5, 1, 3 );
		const Matrix2d<TypeParam>& actual = m.getInverse();
		const Matrix2d<TypeParam> expected(3, -5, -1, 2 );
		EXPECT_EQ(expected, actual);
	}
}


TYPED_TEST(Matrix2dTest, TestProduct)
{
	{
		const auto& m0 = Matrix2d<TypeParam>::Identity();
		const auto& m1 = Matrix2d<TypeParam>::Identity();
		const auto& actual = m0 * m1;
		const auto& expected = Matrix2d<TypeParam>::Identity();
		EXPECT_EQ(expected, actual);
	}

	{
		const auto& m0 = Matrix2d<TypeParam>::Identity();
		const auto& m1 = Matrix2d<TypeParam>::Zero();
		const auto& actual = m0 * m1;
		const auto& expected = Matrix2d<TypeParam>::Zero();
		EXPECT_EQ(expected, actual);
	}
}

TYPED_TEST(Matrix2dTest, TestScale)
{
	{
		const Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		const Matrix2d<TypeParam> actual = m.getScaled(2.0);
		const Matrix2d<TypeParam> expected
			(
			2.0, 0.0,
			0.0, 2.0
			);
		EXPECT_EQ(expected, actual);
	}

	{
		Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
		m.scale(2.0f);
		const Matrix2d<TypeParam> expected
			(
			2.0, 0.0,
			0.0, 2.0
			);
		EXPECT_EQ(expected, m);
	}
}

TYPED_TEST(Matrix2dTest, TestToArray)
{
	Matrix2d<TypeParam> m = Matrix2d<TypeParam>::Identity();
	const auto& values = m.toArray2x2();
	EXPECT_EQ(4, values.size());
	EXPECT_EQ(1, values[0]);
	EXPECT_EQ(0, values[1]);
	EXPECT_EQ(0, values[2]);
	EXPECT_EQ(1, values[3]);
}


TYPED_TEST(Matrix2dTest, TestGetEigenValues)
{
	Matrix2d<TypeParam> m(3, 1, 2, 2);
	auto eigens = m.getEigenValues();
	auto expected = std::array<TypeParam, 2>{ 1, 4 };
	EXPECT_EQ(expected, eigens);
}