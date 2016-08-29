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

TEST(SphereTest, TestGetPositionByAngle)
{
	using T = float;
	const Sphere<T> s(Vector3d<T>(0.0, 0.0, 0.0), 1.0f);
	EXPECT_EQ(Vector3d<T>(0, 0,-1), s.getPosition(Angle<T>::Zero(), -Angle<T>::HalfPI()));
	EXPECT_EQ(Vector3d<T>(1, 0, 0), s.getPosition(Angle<T>::Zero(), Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>(0, 0, 1), s.getPosition(Angle<T>::Zero(), Angle<T>::HalfPI()));

	EXPECT_EQ(Vector3d<T>(0, 0,-1), s.getPosition(Angle<T>::HalfPI(), -Angle<T>::HalfPI()));
	EXPECT_EQ(Vector3d<T>(0, 1, 0), s.getPosition(Angle<T>::HalfPI(), Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>(0, 0, 1), s.getPosition(Angle<T>::HalfPI(), Angle<T>::HalfPI()));

	EXPECT_EQ(Vector3d<T>( 0, 0,-1), s.getPosition(Angle<T>::PI(),-Angle<T>::HalfPI()));
	EXPECT_EQ(Vector3d<T>(-1, 0, 0), s.getPosition(Angle<T>::PI(), Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>( 0, 0, 1), s.getPosition(Angle<T>::PI(), Angle<T>::HalfPI()));

	EXPECT_EQ(Vector3d<T>(0, 0,-1), s.getPosition(Angle<T>::HalfPI()*3, -Angle<T>::HalfPI()));
	EXPECT_EQ(Vector3d<T>(0,-1, 0), s.getPosition(Angle<T>::HalfPI()*3, Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>(0, 0, 1), s.getPosition(Angle<T>::HalfPI()*3, Angle<T>::HalfPI()));

	EXPECT_EQ(Vector3d<T>( 0, 0,-1), s.getPosition(Angle<T>::DoublePI(),-Angle<T>::HalfPI()));
	EXPECT_EQ(Vector3d<T>( 1, 0, 0), s.getPosition(Angle<T>::DoublePI(), Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>( 0, 0, 1), s.getPosition(Angle<T>::DoublePI(), Angle<T>::HalfPI()));
}

TEST(SphereTest, TestGetPositionByParam)
{
	const Sphere<float> s(Vector3d<float>(0.0, 0.0, 0.0), 1.0f);
	EXPECT_EQ(Vector3d<float>( 0, 0,-1), s.getPosition(Param<float>(0.0), Param<float>(0.0)));
	EXPECT_EQ(Vector3d<float>( 1, 0, 0), s.getPosition(Param<float>(0.0), Param<float>(0.5)));
	EXPECT_EQ(Vector3d<float>( 0, 0, 1), s.getPosition(Param<float>(0.0), Param<float>(1.0)));

	EXPECT_EQ(Vector3d<float>( 0, 0,-1), s.getPosition(Param<float>(0.5), Param<float>(0.0)));
	EXPECT_EQ(Vector3d<float>(-1, 0, 0), s.getPosition(Param<float>(0.5), Param<float>(0.5)));
	EXPECT_EQ(Vector3d<float>( 0, 0, 1), s.getPosition(Param<float>(0.5), Param<float>(1.0)));

	EXPECT_EQ(Vector3d<float>( 0, 0,-1), s.getPosition(Param<float>(1.0), Param<float>(0.0)));
	EXPECT_EQ(Vector3d<float>( 1, 0, 0), s.getPosition(Param<float>(1.0), Param<float>(0.5)));
	EXPECT_EQ(Vector3d<float>( 0, 0, 1), s.getPosition(Param<float>(1.0), Param<float>(1.0)));


	//EXPECT_EQ(Vector3d<float>(1, 0, 0), s.getPosition(Param<float>(0.0), Param<float>(0.5)));

}