#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "GeometryRenderingSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

#include "../Polygon/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;



void GeometryRenderingSample::setup()
{
	depthTexture.create(Imagef(512, 512), 0);
	depthBuffer.build(depthTexture);
	normalBuffer.build(512, 512);

	renderer.build(512, 512);
	normalRenderer.build();
	onScreenRenderer.build();
	deferredRenderer.build();
}

void GeometryRenderingSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	//Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 5.0f), Vector3d<float>(1.0f, 1.0f, 4.0f));
	Triangle<float> triangle(Vector3d<float>(0.0f, 0.0f, 5.0f), Vector3d<float>(5.0, 0.0, 5.0),Vector3d<float>(0.0, 5.0, 5.0));
	Triangle<float> triangle2(Vector3d<float>(-10.0f, 0.0f, 4.0f), Vector3d<float>(5.0, 0.0, 4.0), Vector3d<float>(0.0, 5.0, 4.0));

	PolygonMesh polygon;
	polygon.add(triangle);
	polygon.add(triangle2);
	TriangleBuffer buffer;
	buffer.add(polygon);

	depthBuffer.bind();
	glViewport(0, 0, 512, 512);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	renderer.render(512, 512,camera, buffer);
	depthBuffer.unbind();

	normalBuffer.bind();
	glViewport(0, 0, 512, 512);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	normalRenderer.render(camera, buffer);
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

	deferredRenderer.render(*depthBuffer.getTexture(), normalTexture, camera, light, material);
	//onScreenRenderer.render(*normalBuffer.getTexture());
}
