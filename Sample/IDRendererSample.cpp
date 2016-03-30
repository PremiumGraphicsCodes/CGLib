#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "IDRendererSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"
#include "../Graphics/TriangleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

IDRendererSample::IDRendererSample()
{
}


void IDRendererSample::setup()
{
	renderer.buildBuildInShader();
	renderer.findLocation();
}

void IDRendererSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	PolygonObject polygon(254);
	polygon.add(box);

	TriangleBuffer buffer;
	buffer.add(polygon);

	renderer.render(camera, buffer);
	/*
	PointBuffer buffer;
	Point point(Vector3d<float>(0.0f, 0.0f, 0.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);
	buffer.add(point);
	renderer->render(camera, buffer);
	*/
}
