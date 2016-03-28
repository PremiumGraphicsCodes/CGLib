#include "gtest/gtest.h"

#include "../Graphics/ColorConverter.h"

using namespace Crystal::Graphics;

TEST( ColorConverterTest, TestToHSV )
{
	using T = float;
	EXPECT_EQ( ColorHSV(   0, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Red() ) );
	EXPECT_EQ( ColorHSV( 120, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Green() ) );
	EXPECT_EQ( ColorHSV( 240, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Blue() ) );
	EXPECT_EQ( ColorHSV(   0, 0, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::White() ) );
	EXPECT_EQ( ColorHSV(   0, 0, 0 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Black() ) );
}

/*
TEST(ColorConverterTest, TestToGrayScale)
{
	using T = float;
	EXPECT_NEAR(, ColorConverter<T>::toGrayScale(ColorRGB<T>::White()), 0.01);
	EXPECT_NEAR(0, ColorConverter<T>::toGrayScale(ColorRGB<T>::Black()), 0.01);
	EXPECT_NEAR(0.299, ColorConverter<T>::toGrayScale(ColorRGB<T>::Red()), 0.01 );
	EXPECT_NEAR(0.587, ColorConverter<T>::toGrayScale(ColorRGB<T>::Green()), 0.01);
	EXPECT_NEAR(0.114, ColorConverter<T>::toGrayScale(ColorRGB<T>::Blue()), 0.01);

	using UC = unsigned char;
	EXPECT_EQ(255, ColorConverter<UC>::toGrayScale(ColorRGB<UC>::White()));
}
*/