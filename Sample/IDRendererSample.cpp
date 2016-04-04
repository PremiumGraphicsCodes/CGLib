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
	frameBuffer.build(512, 512);

	renderer.build();
}

void IDRendererSample::onMiddleButtonDown(float x, float y)
{
	const auto xRatio = x / float(this->width);
	const auto yRatio = y / float(this->height);
	////std::cout << xRatio << std::endl;
	////std::cout << yRatio << std::endl;
	const auto screenx = frameBuffer.getWidth() * xRatio;
	const auto screeny = frameBuffer.getHeight() * yRatio;
	//std::cout << screenx << std::endl;
	//std::cout << screeny << std::endl;
	//const auto c = fb.getColor(screenx, screeny);
	const auto c = frameBuffer.getColor(screenx, frameBuffer.getHeight() - screeny);
	std::cout << (float)c.getRed() << std::endl;
	std::cout << (float)c.getGreen() << std::endl;
	std::cout << (float)c.getBlue() << std::endl;
	std::cout << (float)c.getAlpha() << std::endl;
}


void IDRendererSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	this->width = width;
	this->height = height;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	PolygonObject polygon(255);
	polygon.add(box);

	TriangleBuffer buffer;
	buffer.add(polygon);

	glViewport(0, 0, frameBuffer.getWidth(), frameBuffer.getHeight());
	frameBuffer.bind();
	renderer.render(camera, buffer);
	frameBuffer.unbind();

	glViewport(0, 0, width, height);
	renderer.render(camera, buffer);

	/*
	PointBuffer buffer;
	Point point(Vector3d<float>(0.0f, 0.0f, 0.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);
	buffer.add(point);
	renderer->render(camera, buffer);
	*/
}
