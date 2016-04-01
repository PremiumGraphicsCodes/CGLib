#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "IDRendererSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"
#include "../Shader/FrameBuffer.h"
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
	renderer.build();
}

void IDRendererSample::onLeftButtonDown(float x, float y)
{
	const auto c = fb.getColor(x, 756-y);
	std::cout << (float)c.getRed() << std::endl;
	std::cout << (float)c.getGreen() << std::endl;
	std::cout << (float)c.getBlue() << std::endl;
	std::cout << (float)c.getAlpha() << std::endl;
}


void IDRendererSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	PolygonObject polygon(255);
	polygon.add(box);

	TriangleBuffer buffer;
	buffer.add(polygon);

	
	fb.build(width, height);
	fb.bind();
	renderer.render(camera, buffer);
	fb.unbind();
	renderer.render(camera, buffer);

	/*
	PointBuffer buffer;
	Point point(Vector3d<float>(0.0f, 0.0f, 0.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);
	buffer.add(point);
	renderer->render(camera, buffer);
	*/
}
