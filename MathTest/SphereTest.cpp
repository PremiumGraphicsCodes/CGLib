#include "gtest/gtest.h"
 
#include "../Math/Sphere.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;

using T = float;

TEST( SphereTest, TestConstruct )
{
	Sphere<float> s;
	EXPECT_TRUE( s.isValid() );
	EXPECT_EQ( s, Sphere<float>::UnitSphere() );

	//EXPECT_TRUE( s.isShrinked() );
}

TEST( SphereTest, ShrinkTest )
{

}

TEST( SphereTest, BoundingBoxTest )
{
	Sphere<float> s;
	const Box3d<T>& bb = s.getBoundingBox();
	const Box3d<T> expected( Vector3d<float>( -1.0, -1.0, -1.0 ), Vector3d<float>( 1.0, 1.0, 1.0 ) );
	EXPECT_EQ( expected, bb );
}

TEST( SphereTest, OffsetTest )
{
	Sphere<float> s;
	s.outerOffset( 1.0f );
	EXPECT_EQ( 2.0f, s.getRadius() );

	s.innerOffset( 1.0f );
	EXPECT_EQ( 1.0f, s.getRadius() );
}

TEST(SphereTest, TestIsInner)
{
	Sphere<float> s( Vector3d<float>( 0.0, 0.0, 0.0 ), 1.0f );
	EXPECT_TRUE( s.isInner(Vector3d<float>(0.0f, 0.0f, 0.0f) ) );
	EXPECT_FALSE( s.isInner(Vector3d<float>( 2.0f, 0.0f, 0.0f) ) );
}

TEST(SphereTest, TestIsOnStrictly)
{
	Sphere<float> s(Vector3d<float>(0.0, 0.0, 0.0), 1.0f);
	EXPECT_TRUE(s.isOnStrictly(Vector3d<float>(1.0f, 0.0, 0.0f)));
}

TEST(SphereTest, TestGetPosition)
{
	Sphere<float> s(Vector3d<float>(0.0, 0.0, 0.0), 1.0f);
	const auto actual = s.getPosition(Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
	const Vector3d<float>expected(0, 0, 1);
	EXPECT_EQ(expected, actual);
}