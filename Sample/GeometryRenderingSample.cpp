#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "GeometryRenderingSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

#include "../Polygon/PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;



void GeometryRenderingSample::setup()
{
	depthBuffer.build(512, 512, 0);
	normalBuffer.build(512, 512, 1);

	renderer.build(512, 512);
	normalRenderer.build(512, 512);
	onScreenRenderer.build();
	deferredRenderer.build();
}

void GeometryRenderingSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	depthBuffer.bind();
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	PolygonObject polygon;
	polygon.add(box);
	TriangleBuffer buffer;
	buffer.add(polygon);
	glEnable(GL_DEPTH_TEST);
	renderer.render(width, height,camera, buffer);
	depthBuffer.unbind();

	normalBuffer.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	normalRenderer.render(width, height, camera, buffer);
	normalBuffer.unbind();

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0, 10.0, 10.0));
	light.setDiffuse(ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	light.setAmbient(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	light.setSpecular(ColorRGBA<float>(0.0, 1.0, 0.0, 1.0));
	Material material;
	material.setDiffuse(ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	material.setAmbient(ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	material.setSpecular(ColorRGBA<float>(0.0, 1.0, 0.0, 1.0));
	material.setShininess(1.0f);
	deferredRenderer.render(*depthBuffer.getTexture(), *normalBuffer.getTexture(), camera, light, material);
	//onScreenRenderer.render(*normalBuffer.getTexture());
}
