#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "SmoothRendererSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/Material.h"

#include "../Polygon/PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

SmoothRendererSample::SmoothRendererSample()
{
}


void SmoothRendererSample::setup()
{
	renderer.build();
}

void SmoothRendererSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0f, 10.0f, -10.0f));
	light.setDiffuse(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));


	Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	PolygonMesh polygon;
	polygon.add(box);
	TriangleBuffer buffer;
	buffer.add(polygon);
	Material material;
	material.setAmbient(ColorRGBA<float>(0.2, 0.2, 0.2, 0.0));
	renderer.render(camera, buffer, light, material);
}
