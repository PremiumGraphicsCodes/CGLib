#if _WIN64
#include "windows.h"
#endif

#include "gtest\gtest.h"

#include "../Shader/DepthRenderer.h"
#include "../Shader/FrameBuffer.h"
#include "../Shader/Texture.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/OrthogonalCamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(DepthRendererTest, Test)
{
	int width = 32;
	int height = 32;
	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	Buffer3d<float> buffer;
	buffer.add( Vector3d<float>(-0.25,-0.25,-5) );
	buffer.add( Vector3d<float>(0.25,-0.25,-5) );
	buffer.add( Vector3d<float>(0.25, 0.25, -5) );
	buffer.add( Vector3d<float>(-0.25,0.25,-5) );

	DepthRenderer renderer;
	renderer.setBuffers({ buffer });
	renderer.build(Crystal::File("../GLSL/depth.vs"), Crystal::File("../GLSL/depth.fs"));

	OrthogonalCamera<float> camera;
	glViewport(0, 0, width, height);
	renderer.render(camera);

	const auto actual = frame.toImage();
	actual.save("../TestFile/Shader/DepthActual.png", ImageFileFormat::PNG);
	//const auto expected = ImageRGBA<unsigned char>::Red(width, height);
	//EXPECT_EQ(expected, actual);
}