#if _WIN64
#include "windows.h"
#endif

#include "gtest\gtest.h"

#include "../Shader/NormalRenderer.h"

#include "../Shader/FrameBuffer.h"
#include "../Graphics/PerspectiveCamera.h"


using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(NormalRendererTest, Test)
{
	const int width = 32;
	const int height = 32;

	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	Crystal::File vsFile("../GLSL/billboard.vs");
	Crystal::File fsFile("../GLSL/billboard.fs");
	//ShaderObject object;

	NormalRenderer<float> renderer;
	renderer.build(vsFile, fsFile);

	PerspectiveCamera<float> camera;
	glViewport(0, 0, width, height);
	renderer.render(camera);

	const auto& actual = frame.toImage();
	actual.save("../TestFile/Shader/NormalActual.png", ImageFileFormat::PNG);
}