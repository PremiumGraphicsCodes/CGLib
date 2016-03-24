#include "FluidSample.h"
#include "AntTweakBar.h"

#include "../Physics/Fluid.h"
#include "../Physics/SPHParticle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Shader/LegacyRenderer.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Graphics/Light.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidSample::setup()
{
	SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
	Box<float> box(Vector3d<float>(0.0f, 0.0f, -10.0f), Vector3d<float>(20.0f, 20.0f, 0.0f));
	fluid = std::make_unique<Fluid>(box, 1.0f, constant);
	world.add(fluid.get());
	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box<float> boundary( Vector3d<float>(-10.0, 0.0f, -10.0 ), Vector3d<float>(40.0, 1000.0, 0.0 ));
	world.setBoundary(boundary);
}

void FluidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	
	const float effectLength = 1.25f;
	world.simulate(effectLength, 0.01f);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(-20.0, -5.0, -10.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	PointBuffer buffer;
	buffer.add(*fluid.get());
	renderer.render(camera, buffer);
}
