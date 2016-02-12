#include "GLee.h"
#include "VisualObject.h"

#include "../Graphics/Light.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void VisualObject::render(const ICamera<float>& camera, RenderingMode mode)
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	const auto xaxis = Line3d<float>(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	const auto yaxis = Line3d<float>(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 1, 0));
	const auto zaxis = Line3d<float>(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 1));

	LineBuffer axisBuffer;
	axisBuffer.add(xaxis, ColorRGBA<float>(1.0, 0.0, 0.0, 1.0));
	axisBuffer.add(yaxis, ColorRGBA<float>(0.0, 1.0, 0.0, 1.0));
	axisBuffer.add(zaxis, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));

	//glClear(GL_DEPTH_BUFFER_BIT);


	if (mode == RenderingMode::Wireframe) {
		renderer.render(camera, lineBuffer);
		//renderer.render(camera, boneLineBuffer);
	}
	else if (mode == RenderingMode::Point) {
		renderer.render(camera, pointBuffer);
	}
	else if (mode == RenderingMode::ID) {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.renderId(camera, triangleBuffer);
	}
	else if (mode == RenderingMode::Volume) {
		renderer.renderAlphaBlend(camera, pointBuffer);
	}
	else {
		PointLight<float> light;
		light.setPos(Vector3d<float>(-10.0, 10.0, 10.0));
		light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));
		renderer.render(camera, light, triangleBuffer);
	}

	renderer.render(camera, axisBuffer);
}