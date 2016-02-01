#include "gtest/gtest.h"

#include "../Graphics/ColorConverter.h"

using namespace Crystal::Graphics;

TEST( ColorConverterTest, TestToHSV )
{
	using T = float;
	EXPECT_EQ( ColorHSV<T>(   0, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Red() ) );
	EXPECT_EQ( ColorHSV<T>( 120, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Green() ) );
	EXPECT_EQ( ColorHSV<T>( 240, 1, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Blue() ) );
	EXPECT_EQ( ColorHSV<T>(   0, 0, 1 ), ColorConverter<T>::toHSV( ColorRGBA<T>::White() ) );
	EXPECT_EQ( ColorHSV<T>(   0, 0, 0 ), ColorConverter<T>::toHSV( ColorRGBA<T>::Black() ) );
}

TEST( ColorConverterTest, TestToRGB )
{
	using T = float;
	EXPECT_EQ( ColorRGBA<T>::Red(),		ColorConverter<T>::toRGB( ColorHSV<T>(   0, 1, 1 ) ) );
	EXPECT_EQ( ColorRGBA<T>::Green(),	ColorConverter<T>::toRGB( ColorHSV<T>( 120, 1, 1 ) ) );
	EXPECT_EQ( ColorRGBA<T>::Blue(),		ColorConverter<T>::toRGB( ColorHSV<T>( 240, 1, 1 ) ) );
	EXPECT_EQ( ColorRGBA<T>::White(),	ColorConverter<T>::toRGB( ColorHSV<T>(   0, 0, 1 ) ) );
	EXPECT_EQ( ColorRGBA<T>::Black(),	ColorConverter<T>::toRGB( ColorHSV<T>(   0, 0, 0 ) ) );
	//ColorConverter<T>::toRGB( ColorHSV<T>( 3, 1, 1 ) );
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