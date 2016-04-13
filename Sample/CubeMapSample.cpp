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
	Crystal::Graphics::Image<float> image(2, 2);
	image.setColor(0, 0, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	image.setColor(0, 1, ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	image.setColor(1, 0, ColorRGBA<float>(0.0, 1.0, 0.0, 1.0));

	image.setColor(1, 1, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	cubeMapTexture.create(image, 10);

	renderer.build();
	//renderer.build(512, 512);

	Triangle<float> triangle1(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0));
	Triangle<float> triangle2(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0), Vector3d<float>(-10.0, 10.0, 0.0));

	polygon.add(triangle1); 
	polygon.add(triangle2);

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
		renderer.render(cubeMapTexture, camera, buffer, true);

	}
	{
		Crystal::Graphics::TriangleBuffer buffer;
		buffer.add(polygon);

		renderer.render(cubeMapTexture, camera, buffer, false);
	}
}
