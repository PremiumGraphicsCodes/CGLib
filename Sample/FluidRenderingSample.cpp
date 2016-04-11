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
	depthBuffer.build(512, 512, 0);
	normalBuffer.build(512, 512, 1);
	volumeBuffer.build(512, 512, 2);
	bluredBuffer.build(512, 512, 3);

	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	pointRenderer.build();
	absorptionRenderer.build();

	bilateralFilter.build();
}

void FluidRendererSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointBuffer buffer;
	Point point1(Vector3d<float>(0.0f, 0.0f, 1.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 1000.0f);
	Point point2(Vector3d<float>(1.0f, 0.0f, -1.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 1000.0f);

	//Point point3(Vector3d<float>(-1.0f, 0.0f, -1000.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100000.0f);

	buffer.add(point1);
	buffer.add(point2);
	//buffer.add(point3);

	glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
	depthBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	depthRenderer.render(camera, buffer);
	depthBuffer.unbind();

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredBuffer.bind();
	bilateralFilter.render(*depthBuffer.getTexture());
	bluredBuffer.unbind();

	glViewport(0, 0, normalBuffer.getWidth(), normalBuffer.getHeight());
	normalBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	normalFilter.render(*depthBuffer.getTexture(), camera);
	normalBuffer.unbind();

	PointLight<float> light;
	light.setPos(Vector3d<float>(0.0, 0.0, 0.0));
	light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 0.0));
	light.setSpecular(ColorRGBA<float>(1.0, 1.0, 1.0));
	light.setAmbient(ColorRGBA<float>(0.0, 0.0, 0.0));

	Material material;
	material.setDiffuse(ColorRGBA<float>(1.0, 0.0, 0.0));
	material.setSpecular(ColorRGBA<float>(1.0, 1.0, 1.0));
	material.setAmbient(ColorRGBA<float>(0.0, 0.0, 0.0));
	material.setShininess(1.0f);

	glViewport(0, 0, width, height);//depthBuffer.getWidth(), depthBuffer.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(*depthBuffer.getTexture(), *normalBuffer.getTexture(), camera, light, material);
	//glViewport(0, 0, width, height);
	//renderer.render(camera, buffer);
	return;

	glViewport(0, 0, width, height);
	volumeBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointRenderer.render(camera, buffer);
	volumeBuffer.unbind();

	//absorptionRenderer.render(*volumeBuffer.getTexture());

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	absorptionRenderer.render(*volumeBuffer.getTexture());


}
