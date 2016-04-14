#include "FluidRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidRenderer::build(const int width, const int height)
{
	depthBuffer.build(width, height, 0);
	normalBuffer.build(width, height, 1);
	volumeBuffer.build(width, height, 2);
	bluredBuffer1.build(width, height, 3);
	bluredBuffer2.build(width, height, 4);
	shadedBuffer.build(width, height, 5);
	cubeMapBuffer.build(width, height, 6);
	absorptionBuffer.build(width, height, 7);

	Crystal::Graphics::Imagef image1;
	image1.read("../Shader/cube_PX.png");
	Crystal::Graphics::Imagef image2;
	image2.read("../Shader/cube_NX.png");
	Crystal::Graphics::Imagef image3;
	image3.read("../Shader/cube_PY.png");
	Crystal::Graphics::Imagef image4;
	image4.read("../Shader/cube_NY.png");
	Crystal::Graphics::Imagef image5;
	image5.read("../Shader/cube_PZ.png");
	Crystal::Graphics::Imagef image6;
	image6.read("../Shader/cube_NZ.png");

	cubeMapTexture.create(image1, 10);
	cubeMapTexture.setNegativeX(image2);
	cubeMapTexture.setPositiveY(image3);
	cubeMapTexture.setNegativeY(image4);
	cubeMapTexture.setPositiveZ(image5);
	cubeMapTexture.setNegativeZ(image6);

	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	pointRenderer.build();
	absorptionRenderer.build();
	skyBoxRenderer.build();

	bilateralFilter.build();

	cubeMapRenderer.build();

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
	light.setPos(Vector3d<float>(10.0, 10.0, 10.0));
	light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 0.0));
	light.setSpecular(ColorRGBA<float>(0.0, 0.0, 1.0));
	light.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));

	Material material;
	material.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0));
	material.setSpecular(ColorRGBA<float>(0.0, 0.0, 1.0));
	material.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));
	material.setShininess(10.0f);

	glViewport(0, 0, bluredBuffer2.getWidth(), bluredBuffer2.getHeight());//depthBuffer.getWidth(), depthBuffer.getHeight());
	shadedBuffer.bind();
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(*bluredBuffer2.getTexture(), *normalBuffer.getTexture(), camera, light, material);
	shadedBuffer.unbind();

	glViewport(0, 0, cubeMapBuffer.getWidth(), cubeMapBuffer.getHeight());
	cubeMapBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cubeMapRenderer.render(*bluredBuffer2.getTexture(), *normalBuffer.getTexture(), camera, cubeMapTexture);
	cubeMapBuffer.unbind();

	glViewport(0, 0, volumeBuffer.getWidth(), volumeBuffer.getHeight());
	volumeBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pointRenderer.render(camera, buffer);
	volumeBuffer.unbind();

	//absorptionRenderer.render(*volumeBuffer.getTexture());

	glViewport(0, 0, absorptionBuffer.getWidth(), absorptionBuffer.getHeight());
	absorptionBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	absorptionRenderer.render(*volumeBuffer.getTexture());
	absorptionBuffer.unbind();

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	{
		Crystal::Polygon::PolygonObject polygon;
		//const Box3d<float> box(Vector3d<float>(-100.0, 0.0, -20.0), Vector3d<float>(100.0, 20.0, 20.0));
		//polygon.add(box);
		Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-100.0, -100.0, -100.0), Crystal::Math::Vector3d<float>(100.0, 100.0, 100.0));
		polygon.add(box);
		TriangleBuffer triBuffer;
		triBuffer.add(polygon);
		skyBoxRenderer.render(cubeMapTexture, camera, triBuffer);
	}
	*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//onScreenRenderer.render(*absorptionBuffer.getTexture(), 0.75f);
	onScreenRenderer.render(*cubeMapBuffer.getTexture(), 1.0f);
	//onScreenRenderer.render(*shadedBuffer.getTexture(), 0.25f);

	glDisable(GL_BLEND);

}
