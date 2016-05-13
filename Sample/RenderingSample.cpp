#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "RenderingSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void RenderingSample::setup()
{
	onScreenRenderer.build();
}

void RenderingSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	LineBuffer buffer;
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(line, color);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.render(camera, buffer);
}
