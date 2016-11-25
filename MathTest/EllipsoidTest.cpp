#include "gtest\gtest.h"

#include "../Math/Ellipsoid.h"
#include "../Math/Curve3d.h"

using namespace Crystal::Math;

template<class T>
class EllipsoidTest : public testing::Test {
};

using TestTypes = ::testing::Types<float, double>;

TYPED_TEST_CASE(EllipsoidTest, TestTypes);

TYPED_TEST(EllipsoidTest, TestGetVolume)
{
	using T = float;
	{
		Ellipsoid<T> e(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
		const auto expected = Tolerance<T>::getPI() * T{ 4 } / T{ 3 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}
	{
		Ellipsoid<T> e(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 1, 1));
		const auto expected = Tolerance<T>::getPI() * T { 4 } / T{ 3 } *T{ 2 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}
}

TYPED_TEST(EllipsoidTest, TestGetPosition)
{
	using T = float;
	Ellipsoid<T> e(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1), Quaternion<T>(0,0,0,1));

	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(0)), Angle<T>(Degree<T>(0)));
		Vector3d<T> expected(1, 0, 0);
		EXPECT_EQ(expected, actual);
	}


	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(180)), Angle<T>(Degree<T>(0)));
		Vector3d<T> expected(-1, 0, 0);
		EXPECT_EQ(expected, actual);
	}

	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(0)), Angle<T>(Degree<T>(90)));
		Vector3d<T> expected(0, 0, 1);
		EXPECT_EQ(expected, actual);
	}

}

TYPED_TEST(EllipsoidTest, TestToCurve3d)
{
	using T = float;
	{
		Ellipsoid<T> e(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
		const auto& actual = e.toCurve3d(2, 2);
	}
}

TEST(EllipsoidTest, TestGetTranslateMatrix)
{
	using T = float;
	Ellipsoid<T> e(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	EXPECT_EQ( Matrix3d<T>::Zero(), e.getTranslateMatrix() );
	EXPECT_EQ( Matrix3d<T>::Identity(), e.getScalingMatrix());
}
