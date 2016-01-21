#if _WIN64
#include "windows.h"
#endif

#include "gtest/gtest.h"

#include "../Shader/BillBoardRenderer.h"

#include "../Graphics/Image.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"

#include "../Shader/FrameBuffer.h"
#include "../Graphics/PerspectiveCamera.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(BillBoardRendererTest, Test)
{
	const int width = 2;
	const int height = 2;

	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	Image<unsigned char> image(2, 2);
	image.setColor(0, 0, ColorRGBA<unsigned char>::Red());
	image.setColor(1, 0, ColorRGBA<unsigned char>::Green());
	image.setColor(0, 1, ColorRGBA<unsigned char>::Black());
	image.setColor(1, 1, ColorRGBA<unsigned char>::White());
	Crystal::Shader::Texture<unsigned char> texture(image);
	texture.bind();


	Crystal::File vsFile("../GLSL/billboard.vs");
	Crystal::File gsFile("../GLSL/billboard.gs");
	Crystal::File fsFile("../GLSL/billboard.fs");
	ShaderObject object;
	BillBoardRenderer<float> renderer(object);
	renderer.build(vsFile, gsFile, fsFile);
	renderer.findLocation();
	glViewport(0, 0, width, height);


	PerspectiveCamera<float> camera;
	Vector3d<float> point(0, 0, -5);

	Buffer3d<float> buffer;
	buffer.add(point);
	Buffer1d<float> densityBuffer;
	densityBuffer.add(1.0);
	renderer.setBuffers({ buffer, densityBuffer});
	glViewport(0, 0, width, height);
	renderer.render(camera);

	texture.unbind();

	EXPECT_TRUE(frame.unbind());


	const auto& actual = frame.toImage();
	actual.save("../TestFile/Shader/BillBoardActual.png", ImageFileFormat::PNG);

	const auto& expected = image;
	EXPECT_EQ(expected, actual);
}
