#if _WIN64
#include "windows.h"
#endif

#include "gtest/gtest.h"

#include "../Shader/FrameBuffer.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(FrameBufferTest, Test)
{
	const int width = 32;
	const int height = 32;

	FrameBuffer buffer;
	EXPECT_TRUE( buffer.build(width, height) );
	EXPECT_TRUE( buffer.bind() );
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	const auto& actual = buffer.toImage();

	Image<unsigned char> expected = Image<unsigned char>::Blue(32, 32);

	EXPECT_EQ(expected, actual);

//depth.save("../TestFile/Shader/DepthActual.png", ImageFileFormat::PNG);
	EXPECT_TRUE(buffer.unbind());

}