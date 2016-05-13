#include "ParticleSample.h"

#include "../Math/Space3d.h"
#include "../Math/Sphere.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/ColorRGBA.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void ParticleSample::setup()
{
	particle = std::make_unique<ParticleObject>();
	//Sphere<float> sphere(Vector3d<float>(0.0f, 0.0f, 0.0f), 1.0f);
	//particle->add(sphere, 0.1f, 1.0f);
	//particle->toVolumes(1.25f);
	Particle p(Vector3d<float>(0.0f, 0.0f, 0.0f),1.0f, 1.0f);
	particle->add(p);
	Space3d<float> space(Vector3d<float>(-2, -2, -2), Vector3d<float>(4, 4, 4));
	polygon.reset( particle->toPolygon(0.5f, 0.5f, space ) );
}

void ParticleSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	buffer.add(*particle);
	renderer.render(camera, buffer);

	LineBuffer lineBuffer;
	lineBuffer.add(*polygon, ColorRGBA<float>(0.0, 0.0, 0.0, 1.0));
	renderer.render(camera, lineBuffer);
}