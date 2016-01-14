#include "gtest/gtest.h"
#include "../Graphics/LineBuffer.h"

using namespace Crystal;

TEST(LineBufferTest, Test)
{
	Math::Line3d<float> l(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));
	const auto color = Graphics::ColorRGBA<float>::Black();
	Graphics::Line line(l, color);
	EXPECT_EQ( l, line.getLine() );
	EXPECT_EQ(color, line.getColor());
}

TEST(LineBufferTest, TestAdd)
{
	Math::Line3d<float> l(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));
	const auto color = Graphics::ColorRGBA<float>::Black();
	Graphics::Line line(l, color);

	Graphics::LineBuffer buffer;
	buffer.add(line);
	EXPECT_EQ( 2, buffer.getBuffers().size() );
}