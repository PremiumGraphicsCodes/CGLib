#if _WIN64
#include "windows.h"
#endif

#include "../Shader/LineRenderer.h"

#include "gtest/gtest.h"

#include "../Graphics/ImageRGBA.h"
#include "../Shader/FrameBuffer.h"
#include "../Graphics/OrthogonalCamera.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(LineRendererTest, Test)
{
	const int width = 8;
	const int height = 8;

	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());

	glClearColor(0.0, 0.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LineRenderer<float> renderer;
	renderer.build(Crystal::File("../GLSL/line.vs"), Crystal::File("../GLSL/line.fs"));
	renderer.findLocation();
	OrthogonalCamera<float> camera;

	Line line(Line3d<float>(Vector3d<float>(-1, 0, -5), Vector3d<float>(1, 0, -5)), ColorRGBA<float>(1, 0,0,1));
	LineBuffer buffer;
	buffer.add(line);

	glViewport(0, 0, width, height);

	renderer.setBuffer( buffer );
	renderer.render(camera);
	
	const auto image = frame.toImage();
	image.save("../TestFile/Shader/LineActual.png", ImageFileFormat::PNG);

	ImageRGBA<unsigned char> expected("../TestFile/Shader/LineExpected.png");

	frame.unbind();

	EXPECT_EQ(expected, image);

}
