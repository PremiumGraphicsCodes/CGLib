#if _WIN64
#include "windows.h"
#endif
#include "../Graphics/PointBuffer.h"
#include "../Shader/ShaderObject.h"

#include "Cursor3dSample.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void Cursor3dSample::setup()
{
	cursor = Vector3d<float>(0.0f, 0.0f, 0.0f);
	renderer.build();
}

void Cursor3dSample::onMiddleDragging(const float dx, const float dy)
{
	Vector3d<float> v(-dx*0.1f, dy*0.1f, 0.0f);
	v = v.getMult(rotationMatrix);
	cursor += v;
}


void Cursor3dSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	this->rotationMatrix = camera.getRotationMatrix();
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointBuffer buffer;
	Point point( cursor, ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 100.0f);
	buffer.add(point);
	renderer.render(camera, buffer);
}