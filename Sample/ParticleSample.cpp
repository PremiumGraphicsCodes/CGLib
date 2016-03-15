#include "ParticleSample.h"

#include "../Math/Space3d.h"
#include "../Math/Sphere.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void ParticleSample::setup()
{
	particle = std::make_unique<ParticleObject>();
	Sphere<float> sphere(Vector3d<float>(0.0f, 0.0f, 0.0f), 1.0f);
	particle->add(sphere, 0.1f, 1.0f);
	//particle->toVolumes(1.25f);
}

void ParticleSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, -2.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	PointBuffer buffer;
	buffer.add(*particle);
	renderer.render(camera, buffer);

	/*
	LineBuffer lineBuffer;
	lineBuffer.add(*polygon);
	renderer.render(camera, lineBuffer);
	*/
}