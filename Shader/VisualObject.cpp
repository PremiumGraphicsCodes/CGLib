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

	for (auto o : objects) {
		o->render(camera);
	}
	/*
	if (mode == RenderingMode::Wireframe) {
		line.render(camera);
		//renderer.render(camera, boneLineBuffer);
	}
	else if (mode == RenderingMode::Point) {
		point.render(camera);
	}
	else if(mode == RenderingMode::Surface){
		triangle.render(camera);
	}
	*/
	renderer.render(camera, axisBuffer);
}