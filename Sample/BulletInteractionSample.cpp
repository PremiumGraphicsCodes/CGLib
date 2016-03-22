#include "BulletInteractionSample.h"

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

void BulletInteractionSample::setup()
{
	rigid = std::make_unique<BulletRigid>(Vector3d<float>(2.0f, 2.0f, 2.0f), Vector3d<float>(-1.0f, -2.0f, -1.0f), 10.0f);
	bulletWorld.add(rigid.get());

	{
		ground = std::make_unique<BulletRigid>(Vector3d<float>(50.0f, 5.0f, 50.0f), Vector3d<float>(0.0f, -10.0f, 0.0f), 0.0f);
		bulletWorld.add(ground.get());
	}
	bulletWorld.setExternalForce(Vector3d<float>(0, -9.8, 0));

	{
		std::vector<SPHParticle*> particles;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 1; ++k) {
					Vector3d<float> pos(i * 1.0f, j * 1.0f, -k * 1.0f);
					SPHParticle* p = new SPHParticle(pos, 0.5f, 1000.0f, 1000.0f, 100.0f);
					particles.push_back(p);
				}
			}
		}
		fluid = std::make_unique<Fluid>(particles);
		particleWorld.add(fluid.get());
		particleWorld.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
		Box<float> boundary(Vector3d<float>(-10.0, -5.0f, -10.0), Vector3d<float>(40.0, 1000.0, 0.0));
		particleWorld.setBoundary(boundary);

	}

	interaction = BulletInteraction(&particleWorld, &bulletWorld);
}

void BulletInteractionSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);

	interaction.simulate(1.0f / 60.0f);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);

	{
		const auto& surfels = rigid->getSurfaceParticles();//rigid->toSurlfes(0.25f).toPositions();
		for (const auto& p : surfels) {
			Crystal::Graphics::Point pt(p->getPosition(), ColorRGBA<float>(1, 0, 0, 1), 10.0f);
			buffer.add(pt);
		}
	}
	{
		const auto& particles = fluid->getParticles();
		for (const auto& p : particles) {
			Crystal::Graphics::Point pt(p->getPosition(), ColorRGBA<float>(0, 0, 1, 1), 10.0f);
			buffer.add(pt);
		}
	}

	renderer.render(camera, buffer);

	/*
	LineBuffer buffer;
	buffer.add(*polygon);
	renderer.render(camera, buffer);
	*/
}
