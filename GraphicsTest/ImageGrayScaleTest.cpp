#include "gtest/gtest.h"

#include "../Graphics/ImageGrayScale.h"

using namespace Crystal::Graphics;

using T = float;

TEST(ImageGrayScaleTest, TestConstruct)
{
	ImageGrayScale<T> image;
	EXPECT_EQ(0, image.getWidth());
	EXPECT_EQ(0, image.getHeight());
	EXPECT_TRUE(image.getValues().empty());
}

TEST(ImageGrayScaleTest, TestGetValue)
{
	std::vector<T> values{ 0, 0.1f, 0.2f, 0.3f };
	ImageGrayScale<T> image( 2, 2, values );
	EXPECT_EQ( 0.0f, image.getValue(0, 0));
	EXPECT_EQ( 0.1f, image.getValue(0, 1));
}

TEST(ImageGrayScaleTest, TestConstant)
{
	EXPECT_EQ(T{ 0 }, ImageGrayScale<T>::White(1, 1).getValue(0,0));
	EXPECT_EQ(T{ 255 }, ImageGrayScale<T>::Black(1, 1).getValue(0,0));
}

TEST(ImageGrayScaleTest, TestCopy)
{
	std::vector<T> values{ 0, 0.1f, 0.2f, 0.3f };
	ImageGrayScale<T> image(2, 2, values);
	auto copy = image;
}