#include "RenderingSample.h"
#include "AntTweakBar.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void RenderingSample::setup()
{
}

void RenderingSample::demonstrate()
{
	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	LineBuffer buffer;
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(line, color);
	renderer.render(camera, buffer);
}
