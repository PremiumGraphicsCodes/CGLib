#include "gtest/gtest.h"
 
#include "../Graphics/Image.h"

using namespace Crystal::Graphics;

TEST( ImageRGBATest, ContructTest )
{
	Image image;
	EXPECT_EQ( 0, image.getWidth() );
	EXPECT_EQ( 0, image.getHeight() );
	EXPECT_TRUE( image.getValues().empty() );
}

TEST( ImageRGBATest, TestGetColor )
{
	{
		Image color(2, 1);
		color.setColor(0, 0, ColorRGBA<unsigned char>::Red());
		EXPECT_EQ(ColorRGBA<unsigned char>::Red(), color.getColor(0, 0));
		EXPECT_EQ(ColorRGBA<unsigned char>(0, 0, 0, 0), color.getColor(1, 0));
	}

	{
		std::vector<unsigned char> colors = {
			255, 0 ,0, 255,
			0, 255, 0, 255,
			0, 0, 255, 255,
			255, 255, 255, 255
		};
		Image image(2, 2, colors);
		EXPECT_EQ(ColorRGBA<unsigned char>(255, 0, 0, 255), image.getColor(0, 0));
		EXPECT_EQ(ColorRGBA<unsigned char>(0, 255, 0, 255), image.getColor(1, 0));
		EXPECT_EQ(ColorRGBA<unsigned char>(0, 0, 255, 255), image.getColor(0, 1));
		EXPECT_EQ(ColorRGBA<unsigned char>(255, 255, 255, 255), image.getColor(1, 1));

	}

}

TEST(ImageRGBATest, TestColors)
{
	EXPECT_EQ(ColorRGBA<unsigned char>::Black(), Image::Black(1, 1).getColor(0, 0));
	EXPECT_EQ(ColorRGBA<unsigned char>::White(), Image::White(1, 1).getColor(0, 0));

}



TEST(ImageRGBATest, TestReversed)
{
	auto image = Image::Red(2, 4);
	image.setColor(0, 0, ColorRGBA<unsigned char>(255, 0, 0, 255));
	const auto& actual = image.reversed();
	EXPECT_EQ(ColorRGBA<unsigned char>(255, 0, 0, 255), actual.getColor(0, 3) );

}