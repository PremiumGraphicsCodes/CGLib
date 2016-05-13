#include "VolumeSample.h"

#include "../Math/Space3d.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void VolumeSample::setup()
{
	Space3d<float> space(Vector3d<float>(0, 0,0), Vector3d<float>(1,1,1));
	Grid3d<float> grid(4, 4, 4);
	grid.set(0, 0, 0, 1.0f);
	grid.set(1, 1, 1, 1.0f);
	volume = std::make_unique<Volume>(space, grid);
	polygon.reset(volume->toPolygonObject(0.5f));
}

void VolumeSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	PointBuffer buffer;
	buffer.add(*volume);
	renderer.render(camera, buffer);

	LineBuffer lineBuffer;
	lineBuffer.add(*polygon);
	renderer.render(camera, lineBuffer);
}