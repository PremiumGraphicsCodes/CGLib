#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "PointRendererSample.h"
#include "AntTweakBar.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

PointRendererSample::PointRendererSample()
{
}


void PointRendererSample::setup()
{
	shader.build(Crystal::File("../GLSL/point.vs"), Crystal::File("../GLSL/point.fs"));
	auto pr = new PointRenderer<float>(shader);
	renderer.reset(pr);
	renderer->findLocation();
}

void PointRendererSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointBuffer buffer;
	Point point( Vector3d<float>(0.0f, 0.0f, 0.0f), ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f), 100.0f);
	buffer.add(point);
	renderer->render(camera, buffer);
}
