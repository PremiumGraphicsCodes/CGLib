#if _WIN64
#include "windows.h"
#endif


#include "gtest/gtest.h"

#include "../Graphics/Image.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/FrameBuffer.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/Buffer3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(SmoothRendererTest, Test)
{
	const int width = 32;
	const int height = 32;
	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SmoothRenderer<float> renderer;
	EXPECT_TRUE( renderer.build(Crystal::File("../GLSL/smooth.vs"), Crystal::File("../GLSL/smooth.fs")) );

	PerspectiveCamera<float> camera;

	Crystal::Math::Triangle<float> triangle(
		Vector3d<float>(-1, 0, -5),
		Vector3d<float>(1, 0, -5),
		Vector3d<float>(1, 1, -5)
		);

	TriangleBuffer buffer;
	buffer.add(triangle);

	renderer.setBuffer( buffer );
	glViewport(0, 0, width, height);
	renderer.findLocation();

	renderer.render(camera);

	const auto actual = frame.toImage();
	actual.save("../TestFile/Shader/SmoothActual.png", ImageFileFormat::PNG);

	//ImageRGBA<unsigned char> expected("../TestFile/Shader/SmoothExpected.png");

	frame.unbind();

	//EXPECT_EQ(expected, actual);

}