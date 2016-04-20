#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "FluidRenderingSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


FluidRendererSample::FluidRendererSample()
{
}


void FluidRendererSample::setup()
{
	backgroundBuffer.build(512, 512);
	renderer.build(512, 512);
}

void FluidRendererSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{

	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Point point1(Vector3d<float>(0.0f, 0.0f, 1.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);
	Point point2(Vector3d<float>(1.0f, 0.0f, -1.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);

	//Point point3(Vector3d<float>(-1.0f, 0.0f, -1000.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100000.0f);

	PointBuffer buffer;
	buffer.add(point1);
	buffer.add(point2);
	//buffer.add(point3);

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0, 0.0, 0.0));
	light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 0.0));
	light.setSpecular(ColorRGBA<float>(1.0, 0.0, 0.0));
	light.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));

	Material material;
	material.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0));
	material.setSpecular(ColorRGBA<float>(1.0, 0.0, 0.0));
	material.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));
	material.setShininess(1.0f);

	renderer.render(width, height, camera, buffer, light, material, cubeMapTexture, *backgroundBuffer.getTexture());
}
