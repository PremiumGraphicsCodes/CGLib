#include "FluidSample.h"
#include "AntTweakBar.h"

#include "../Physics/Fluid.h"
#include "../Physics/Particle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidSample::setup()
{

	std::vector<Particle*> particles;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 1; ++k) {
				Particle::Constant constant;
				constant.pressureCoe = 1000.0f;
				constant.diameter = 1.0f;
				constant.viscosityCoe = 1.0f;
				constant.restDensity = 1000.0f;
				Vector3d<float> pos(i * 1.0, j * 1.0, k * 1.0);
				Particle* p = new Particle(constant, pos);
				particles.push_back(p);
			}
		}
	}
	fluid = std::make_unique<Fluid>(particles);
	world.add(fluid.get());
	world.setExternalForce(Vector3d<float>(0.0, -9.8, 0.0));
	Box<float> boundary( Vector3d<float>(-10.0, 0.0, -100.0 ), Vector3d<float>( 11.0, 100.0, 100.0 ));
	world.setBoundary(boundary);
}

void FluidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	
	world.simulate(1.25f, 0.001f);

	PerspectiveCamera<float> camera;
	camera.setPos(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	LegacyRenderer renderer;
	PointBuffer buffer;
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(*fluid);
	renderer.render(camera, buffer);
}

void FluidSample::cleanup()
{

}