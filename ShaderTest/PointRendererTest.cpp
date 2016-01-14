#if _WIN64
#include "windows.h"
#endif

#include "gtest/gtest.h"

#include "../Shader/PointRenderer.h"

#include "../Graphics/ImageRGBA.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"

#include "../Shader/FrameBuffer.h"
#include "../Graphics/OrthogonalCamera.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(PointRendererTest, Test)
{
	const int width = 8;
	const int height = 8;

	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());


	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	Crystal::File vsFile("../GLSL/point.vs");
	Crystal::File fsFile("../GLSL/point.fs");
	PointRenderer<float> renderer;
	renderer.build(vsFile, fsFile);
	renderer.findLocation();
	glViewport(0, 0, width, height);


	OrthogonalCamera<float> camera;
	//Vector3d<float> ;

	Point point( Vector3d<float>(0, 0, -5),ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 10.0f);
	PointBuffer buffer;
	buffer.add(point);
	renderer.setBuffer(buffer);
	glViewport(0, 0, width, height);
	//renderer.changeSize(100);
	renderer.render(camera);

	EXPECT_TRUE(frame.unbind());


	const auto& actual = frame.toImage();
	actual.save("../TestFile/Shader/PointActual.png", ImageFileFormat::PNG);

	ImageRGBA<unsigned char> expected("../TestFile/Shader/PointExpected.png");
	EXPECT_EQ(expected, actual);
}
