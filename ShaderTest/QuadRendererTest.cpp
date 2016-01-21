#if _WIN64
#include "windows.h"
#endif

#include "../Shader/QuadRenderer.h"

#include "gtest/gtest.h"

#include "../Graphics/Image.h"
#include "../Shader/FrameBuffer.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"
#include "../Graphics/OrthogonalCamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(QuadRendererTest, Test)
{
	const int width = 8;
	const int height = 8;

	FrameBuffer frame;
	EXPECT_TRUE(frame.build(width, height));
	EXPECT_TRUE(frame.bind());

	glClearColor(0.0, 0.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderObject shader;
	EXPECT_TRUE( shader.build(Crystal::File("../GLSL/quad.vs"), Crystal::File("../GLSL/quad.fs")) );
	QuadRenderer<float> renderer(shader);
	renderer.findLocation();
	OrthogonalCamera<float> camera;

	Buffer3d<float> buffer;
	buffer.add(Vector3d<float>(-5, 0, -5));
	buffer.add(Vector3d<float>(-5, 5, -5));
	buffer.add(Vector3d<float>(5, 5, -5));
	buffer.add(Vector3d<float>(5, 0, -5));

	Buffer4d<float> colorBuffer;
	colorBuffer.add(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	colorBuffer.add(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	colorBuffer.add(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	colorBuffer.add(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));

	Buffer2d<float> texCoord;
	texCoord.add(Vector2d<float>(0.0, 0.0));
	texCoord.add(Vector2d<float>(0.0, 1.0));
	texCoord.add(Vector2d<float>(1.0, 1.0));
	texCoord.add(Vector2d<float>(1.0, 0.0));

	Image<unsigned char> image(2, 2);
	image.setColor(0, 0, ColorRGBA<unsigned char>::Red());
	image.setColor(1, 0, ColorRGBA<unsigned char>::Green());
	image.setColor(0, 1, ColorRGBA<unsigned char>::Black());
	image.setColor(1, 1, ColorRGBA<unsigned char>::White());
	Crystal::Shader::Texture<unsigned char> texture(image);
	texture.bind();


	glViewport(0, 0, width, height);

	renderer.setBuffers({ buffer, colorBuffer, texCoord });
	renderer.render(camera);

	texture.unbind();

	const auto actual = frame.toImage();
	actual.save("../TestFile/Shader/QuadActual.png", ImageFileFormat::PNG);

	Image<unsigned char> expected("../TestFile/Shader/QuadExpected.png");
	EXPECT_EQ(expected, actual);

	frame.unbind();

	//EXPECT_EQ(expected, image);

}
