#include "stdafx.h"

#include "../Graphics/ColorMap.h"

using namespace Crystal::Graphics;

TEST( RangeTest, TestNormalized )
{
	Range map( 0, 100 );
	EXPECT_EQ( 0.0f, map.getNormalized( 0.0 ) );
	EXPECT_EQ( 1.0f, map.getNormalized( 100.0 ) );
}

TEST( ColorRGBAMapTest, TestConstruct )
{
	ColorMap map( 0, 100, 10 );
	EXPECT_EQ( 10, map.getReds().size() );
	EXPECT_EQ( 10, map.getGreens().size() );
	EXPECT_EQ( 10, map.getBlues().size() );
}

TEST( ColorRGBAMapTest, TestNormalized )
{
	ColorMap map( 0, 100, 10 );
	EXPECT_EQ( 0.0f, map.getNormalized( 0.0 ) );
	EXPECT_EQ( 1.0f, map.getNormalized( 100.0 ) );
}

TEST( ColorRGBAMapTest, TestIndex )
{
	ColorMap map( 0, 100, 10 );
	EXPECT_EQ( 0, map.getIndex( 0.0 ) );
	EXPECT_EQ( 9, map.getIndex( 100.0 ) );
}

TEST( ColorRGBAMapTest, TestColor )
{
	ColorMap map( 0, 100, 10 );
	map.setColor( 0, ColorRGBA<float>::Black() );
	map.setColor( 9, ColorRGBA<float>::White() );
	{
		const ColorRGBA<float>& color = map.getColor( 0.0 );
		EXPECT_EQ( ColorRGBA<float>::Black(), color );
	}
	{
		const ColorRGBA<float>& c = map.getColor( 100.0 );
		EXPECT_EQ( ColorRGBA<float>::White(), c );
	}
}

TEST( ColorRGBAMapTest, TestInterpolatedColor )
{
	ColorMap map( 0, 100, 2 );
	map.setColor( 0, ColorRGBA<float>::Black() );
	map.setColor( 1, ColorRGBA<float>::White() );
	
	const ColorRGBA<float>& color1 = map.getInterpolatedColor( -10.0 );
	EXPECT_EQ( ColorRGBA<float>::Black(), color1 );

	const ColorRGBA<float>& color2 = map.getInterpolatedColor( 200.0 );
	EXPECT_EQ( ColorRGBA<float>::White(), color2 );

	const ColorRGBA<float>& color3 = map.getInterpolatedColor( 50.0 );
	EXPECT_EQ( color3.getRed(), 127.5 );
	EXPECT_EQ( color3.getGreen(), 127.5);
	EXPECT_EQ( color3.getBlue(), 127.5);
	EXPECT_EQ( color3.getAlpha(), 255.0 );
}

TEST( ColorRGBAMapTest, TestValueFromIndex )
{
	ColorMap map( 0, 100, 3 );
	EXPECT_EQ( 0.0, map.getValueFromIndex( 0 ) );
	EXPECT_EQ( 50.0, map.getValueFromIndex( 1  ) );
	EXPECT_EQ( 100.0, map.getValueFromIndex( 2 ) );
}