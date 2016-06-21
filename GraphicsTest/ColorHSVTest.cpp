#include "stdafx.h"

#include "../Graphics/ColorHSV.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(ColorHSVTest, TestToRGBA)
{
	using T = float;
	EXPECT_EQ(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), ColorHSV(0, 1, 1).toColorRGBA());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 1.0f, 0.0f, 1.0f), ColorHSV(120, 1, 1).toColorRGBA());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 1.0f, 1.0f), ColorHSV(240, 1, 1).toColorRGBA());
	EXPECT_EQ(ColorRGBA<float>(1.0f, 1.0f, 1.0f, 1.0f), ColorHSV(0, 0, 1).toColorRGBA());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f), ColorHSV(0, 0, 0).toColorRGBA());
}