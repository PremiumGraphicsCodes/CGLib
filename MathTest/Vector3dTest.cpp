#include "gtest/gtest.h"
 
#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"

using namespace Crystal::Math;

template<class T>
class Vector3dTest : public testing::Test {
};

typedef ::testing::Types<float> TestTypes;

TYPED_TEST_CASE(Vector3dTest, TestTypes);

TYPED_TEST(Vector3dTest, TestConstructByVector2d)
{
	using T = TypeParam;
	const auto expected = Vector3d<T>(1, 2, 0);
	const auto actual = Vector3d<T>( Vector2d<T>( 1, 2 ) );
}

TYPED_TEST(Vector3dTest, TestGet)
{
	using T = TypeParam;
	EXPECT_EQ(0, Vector3d<T>().getX());
	EXPECT_EQ(0, Vector3d<T>().getY());
	EXPECT_EQ(0, Vector3d<T>().getZ());

	EXPECT_EQ(1, Vector3d<T>(1, 2, 3).getX() );
	EXPECT_EQ(2, Vector3d<T>(1, 2, 3).getY() );
	EXPECT_EQ(3, Vector3d<T>(1, 2, 3).getZ() );
}

TYPED_TEST( Vector3dTest, TestEquals )
{
	using T = TypeParam;

	EXPECT_TRUE( Vector3d<T>::Zero().equals( Vector3d<T>::Zero() ) );
	EXPECT_EQ( Vector3d<T>::Zero(), Vector3d<T>::Zero());

	EXPECT_FALSE( Vector3d<T>::Zero().equals( Vector3d<T>::UnitX() ) );
	EXPECT_NE( Vector3d<T>::Zero(), Vector3d<T>::UnitX());
}

TYPED_TEST( Vector3dTest, TestScale )
{
	using T = TypeParam;

	EXPECT_EQ(Vector3d<T>(2, 2, 2), Vector3d<T>(1, 1, 1).scale(2));
	EXPECT_EQ(Vector3d<T>(1, 2, 3), Vector3d<T>(0.5, 1, 1.5).scale(2));
}

TYPED_TEST(Vector3dTest, TestGetLengthSquared)
{
	using T = TypeParam;

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( 3, Vector3d<T>(1,1,1).getLengthSquared() ) );
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(3, Vector3d<T>(1,1,1).getLengthSquared() ) );

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely(14, Vector3d<T>(1, 2, 3).getLengthSquared()));
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(14, Vector3d<T>(1, 2, 3).getLengthSquared()));
}

TYPED_TEST( Vector3dTest, TestGetLength )
{
	using T = TypeParam;
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( std::sqrt( T(3) ), Vector3d<T>(1,1,1).getLength() ) );
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly(std::sqrt( T(3) ), Vector3d<T>(1,1,1).getLength() ) );

	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( std::sqrt( T(14) ) , Vector3d<T>(1, 2, 3).getLength()));
	EXPECT_TRUE( Tolerance<T>::isEqualStrictly( std::sqrt( T(14) ), Vector3d<T>(1, 2, 3).getLength()));

}

TYPED_TEST( Vector3dTest, TestInnerProduct )
{
	using T = TypeParam;
	EXPECT_EQ( 0, Vector3d<T>(0, 0, 0).getInnerProduct(Vector3d<T>(1, 1, 2) ) );
	EXPECT_EQ( 8, Vector3d<T>(2, 2, 2).getInnerProduct(Vector3d<T>(1, 1, 2) ) );
}

TYPED_TEST(Vector3dTest, TestOuterProduct)
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0,0,0), Vector3d<T>(0, 0, 0).getOuterProduct(Vector3d<T>(1, 1, 2)));
	EXPECT_EQ( Vector3d<T>::UnitZ(), Vector3d<T>::UnitX().getOuterProduct(Vector3d<T>::UnitY() ) );
	EXPECT_EQ( Vector3d<T>::UnitX(), Vector3d<T>::UnitY().getOuterProduct(Vector3d<T>::UnitZ() ) );
	EXPECT_EQ( Vector3d<T>::UnitY(), Vector3d<T>::UnitZ().getOuterProduct(Vector3d<T>::UnitX() ) );

}

TYPED_TEST( Vector3dTest, TestGetDistance )
{
	using T = TypeParam;
	const Vector3d<T> v0( 1, 1, 1 );
	const Vector3d<T> v1( 2, 2, 2 );
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( v0.getDistance( v1 ), std::sqrt( T(3) ) ) );
	EXPECT_TRUE( Tolerance<T>::isEqualLoosely( v1.getDistance( v0 ), std::sqrt( T(3) ) ) );
}

TYPED_TEST( Vector3dTest, TestToArray )
{
	using T = TypeParam;
	const Vector3dVector<T> vectors = {
		Vector3d<T>(1, 2, 3),
		Vector3d<T>(4, 5, 6)
	};
	const auto& actual = Vector3d<T>::toArray( vectors );
	const std::vector<T> expected{ 1, 2, 3, 4, 5, 6 };

	EXPECT_EQ( expected, actual );
}

TYPED_TEST(Vector3dTest, TestRotateX)
{
	using T = TypeParam;
	const Matrix3d<T> m = Matrix3d<T>::RotateX( Tolerance<T>::getPI());
	Vector3d<T> v = Vector3d<T>(0.0, 0.0, 1.0);
	v.rotate(m);
	Vector3d<T> expected(0.0, 0.0, -1.0);
	EXPECT_EQ(expected, v);
}

TYPED_TEST(Vector3dTest, TestRotateY)
{
	using T = TypeParam;
	const Matrix3d<T> m = Matrix3d<T>::RotateY( Tolerance<T>::getPI() );
	Vector3d<T> v(1.0, 0.0, 0.0);
	v.rotate(m);
	Vector3d<T> expected(-1.0, 0.0, 0.0);
	EXPECT_EQ(expected, v);
}


TYPED_TEST(Vector3dTest, TestRotateZ)
{
	using T = TypeParam;
	const Matrix3d<T> m = Matrix3d<T>::RotateZ( Tolerance<T>::getPI() );
	Vector3d<T> v(1, 0., 0);
	v.rotate(m);
	Vector3d<T> expected(-1, 0, 0);
	EXPECT_EQ(expected, v);
};

TYPED_TEST(Vector3dTest, TestTransform)
{
	using T = TypeParam;
	const Matrix4d<T> m;
	Vector3d<T> v(1, 0., 0);
	v.transform(m);
}