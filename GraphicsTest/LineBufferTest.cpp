#include "stdafx.h"
#include "../Graphics/LineBuffer.h"

using namespace Crystal;

TEST(LineBufferTest, TestAdd)
{
	Math::Line3d<float> line(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

	Graphics::LineBuffer buffer;
	buffer.add(line, Graphics::ColorRGBA<float>::Black());
	EXPECT_EQ(6, buffer.getPosition().get().size());
}