#include "FluidRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidRenderer::build()
{
	depthBuffer.build(1024, 756, 0);
	normalBuffer.build(1024, 756, 1);
	volumeBuffer.build(1024, 756, 2);
	bluredBuffer1.build(1024, 756, 3);
	bluredBuffer2.build(1024, 756, 4);

	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	pointRenderer.build();
	absorptionRenderer.build();

	bilateralFilter.build();

	onScreenRenderer.build();
}

void FluidRenderer::render(const int width, const int height, const ICamera<float>& camera, const PointBuffer& buffer)
{
	glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
	depthBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	depthRenderer.render(camera, buffer);
	depthBuffer.unbind();

	glViewport(0, 0, bluredBuffer1.getWidth(), bluredBuffer1.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredBuffer1.bind();
	bilateralFilter.render(*depthBuffer.getTexture(), true);
	bluredBuffer1.unbind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredBuffer2.bind();
	bilateralFilter.render(*bluredBuffer1.getTexture(), false);
	bluredBuffer2.unbind();

	glViewport(0, 0, normalBuffer.getWidth(), normalBuffer.getHeight());
	normalBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	normalFilter.render(*bluredBuffer2.getTexture(), camera);
	normalBuffer.unbind();

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0, 10.0, -10.0));
	light.setDiffuse(ColorRGBA<float>(10.0, 0.0, 0.0, 0.0));
	light.setSpecular(ColorRGBA<float>(0.0, 0.0, 1.0));
	light.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));

	Material material;
	material.setDiffuse(ColorRGBA<float>(10.0, 0.0, 0.0));
	material.setSpecular(ColorRGBA<float>(0.0, 0.0, 1.0));
	material.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));
	material.setShininess(100.0f);

	/*
	glViewport(0, 0, width, height);//depthBuffer.getWidth(), depthBuffer.getHeight());
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(*bluredBuffer2.getTexture(), *normalBuffer.getTexture(), camera, light, material);

	glViewport(0, 0, width, height);
	volumeBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointRenderer.render(camera, buffer);
	volumeBuffer.unbind();
	*/

	//absorptionRenderer.render(*volumeBuffer.getTexture());

	/*
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	absorptionRenderer.render(*volumeBuffer.getTexture());
	*/

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	onScreenRenderer.render(*depthBuffer.getTexture());
}
