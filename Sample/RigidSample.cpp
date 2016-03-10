#include "RigidSample.h"

#include <iostream>

#include "../Physics/SPHParticle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void RigidSample::setup()
{
	{
		std::vector<SPHParticle*> particles1;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				for (int k = 0; k < 1; ++k) {
					SPHParticle::Constant constant;
					constant.pressureCoe = 10000.0f;
					constant.diameter = 1.0f;
					constant.viscosityCoe = 1.0f;
					constant.restDensity = 1000.0f;
					Vector3d<float> pos(i * 1.0f, j * 1.0f, k * 1.0f);
					SPHParticle* p = new SPHParticle(constant, pos);
					particles1.push_back(p);
				}
			}
		}
		rigid1 = std::make_unique<Rigid>(particles1);
		world.add(rigid1.get());
	}
	{
		std::vector<SPHParticle*> particles2;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				for (int k = 0; k < 1; ++k) {
					SPHParticle::Constant constant;
					constant.pressureCoe = 10000.0f;
					constant.diameter = 1.0f;
					constant.viscosityCoe = 1.0f;
					constant.restDensity = 1000.0f;
					Vector3d<float> pos(i * 1.0f + 3, j * 1.0f + 5, k * 1.0f);
					SPHParticle* p = new SPHParticle(constant, pos);
					particles2.push_back(p);
				}
			}
		}
		rigid2 = std::make_unique<Rigid>(particles2);
		world.add(rigid2.get());

	}

	world.setExternalForce(Vector3d<float>(0.0f, -9.8f, 0.0f));
	Box<float> boundary(Vector3d<float>(-10.0, 0.0, -100.0), Vector3d<float>(20.0, 100.0, 100.0));
	world.setBoundary(boundary);
}

void RigidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	
	world.simulate(1.25f, 0.001f);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(*rigid1);
	buffer.add(*rigid2);
	renderer.render(camera, buffer);
}
