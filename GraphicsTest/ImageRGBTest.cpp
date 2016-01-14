#include "gtest/gtest.h"
 
#include "../Graphics/ImageRGB.h"

using namespace Crystal::Graphics;

TEST( ImageRGBTest, ContructTest )
{
	ImageRGB<unsigned int> image;
	EXPECT_EQ( 0, image.getWidth() );
	EXPECT_EQ( 0, image.getHeight() );
	EXPECT_TRUE( image.getValues().empty() );
}

TEST( ImageRGBTest, TestEquals )
{
	{
		ImageRGB<float> image1( 1, 1 );
		ImageRGB<float> image2( 2, 2 );
		EXPECT_FALSE( image1.equals( image2 ) );
		EXPECT_TRUE( image1 != image2 );
	}

	{
		ImageRGB<float> image1( 2, 2 );
		ImageRGB<float> image2( 2, 2 );
		EXPECT_TRUE( image1.equals( image2 ) );
		image2.setValue( 0, 0, ColorRGB<float>( 1.0, 0, 0 ) );
		EXPECT_TRUE( image1 != image2 );
	}
}

TEST( ImageRGBTest, TestReds )
{
	{
		ImageRGB<float> image( 2, 2 );
		EXPECT_EQ( 4, image.getReds().size() );
		EXPECT_EQ( 4, image.getGreens().size() );
		EXPECT_EQ( 4, image.getBlues().size() );
	}
}