#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "CubeMapSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


CubeMapSample::CubeMapSample()
{
}

void CubeMapSample::setup()
{
	Crystal::Graphics::Image<unsigned char> image1;//(32, 32);
	/*
	for (int i = 0; i < image.getWidth(); ++i) {
		for (int j = 0; j < image.getHeight(); ++j) {
			if (i % 2 == 0 && j % 2 == 0) {
				image.setColor(i, j, ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));
			}
			else {
				image.setColor(i, j, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0));
			}
		}
	}
	*/
	image1.read("../Shader/cube_PX.png");
	Crystal::Graphics::Image<float> image2(image1.getWidth(), image1.getHeight());
	for (int i = 0; i < image1.getWidth(); ++i) {
		for (int j = 0; j < image1.getHeight(); ++j) {
			const auto r = image1.getColor(i, j).getRed() / 255.0f;
			const auto g = image1.getColor(i, j).getGreen() / 255.0f;
			const auto b = image1.getColor(i, j).getBlue() / 255.0f;
			image2.setColor(i, j, ColorRGBA<float>(r,g,b, 1.0f) );
		}
	}
	//image.setColor(0, 0, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	//image.setColor(0, 1, ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	//image.setColor(1, 0, ColorRGBA<float>(0.0, 1.0, 0.0, 1.0));

	//image.setColor(1, 1, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	cubeMapTexture.create(image2, 10);

	renderer.build();
	skyBoxRenderer.build();
	//renderer.build(512, 512);

	{
		//Triangle<float> triangle1(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0));
		//Triangle<float> triangle2(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0), Vector3d<float>(-10.0, 10.0, 0.0));

		//polygon.add(triangle1);
		//polygon.add(triangle2);
		Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-1.0, -1.0, -1.0), Crystal::Math::Vector3d<float>(1.0, 1.0, 1.0));
		polygon.add(box);
	}

	Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-10.0, -10.0, -10.0), Crystal::Math::Vector3d<float>(10.0, 10.0, 10.0));
	skyPolygon.add(box);
	//polygon.add(box);
}

void CubeMapSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		Crystal::Graphics::TriangleBuffer buffer;
		buffer.add(skyPolygon);
		skyBoxRenderer.render(cubeMapTexture, camera, buffer);

	}
	{
		Crystal::Graphics::TriangleBuffer buffer;
		buffer.add(polygon);

		renderer.render(cubeMapTexture, camera, buffer);
	}
}
