#include "DepthRenderingSample.h"
#include "../Graphics/Light.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void DepthRenderingSample::setup()
{
	depthBuffer.build(512, 512, 0);
	depthRenderer.build();
}

void DepthRenderingSample::demonstrate(const int width, const int height, const ICamera<float>& camera)
{


	glEnable(GL_DEPTH_TEST);
	depthBuffer.bind();
	glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 5.0f), Vector3d<float>(1.0f, 1.0f, 6.0f));
	PolygonObject polygon;
	polygon.add(box);
	TriangleBuffer buffer;
	buffer.add(polygon);
	LegacyRenderer renderer;
	PointLight<float> light;
	renderer.render(camera, light, buffer);
	depthBuffer.unbind();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	depthRenderer.render(*depthBuffer.getTexture());

	//onScreenRenderer.render(*depthBuffer.getTexture(), 1.0);
}