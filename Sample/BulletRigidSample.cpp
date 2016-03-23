#include "BulletRigidSample.h"

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

void BulletRigidSample::setup()
{
	{
		rigid1 = std::make_unique<BulletRigid>(Vector3d<float>(0.5f, 0.5f, 0.5f), Vector3d<float>(0.0f, -2.0f, 0.0f), 10.0f);
		rigid1->getBody()->applyForce(btVector3(2000.0f, 0.0f, 0.0f), btVector3(0.5f, 0.0f, 0.0f));
		//rigid1->getBody()->setAngularVelocity(btVector3(1.0f, 0.0f, 0.0f));
		world.add(rigid1.get());
	}
	{
		rigid2 = std::make_unique<BulletRigid>(Vector3d<float>(0.5f, 2.0f, 0.5f), Vector3d<float>(2.0f, 0.0f, 0.0f), 0.1f);
		world.add(rigid2.get());
	}
	{
		rigid3 = std::make_unique<BulletRigid>(Vector3d<float>(0.5f, 2.0f, 0.5f), Vector3d<float>(2.0f, 10.0f, 0.0f), 0.1f);
		world.add(rigid3.get());
	}


	{
		ground = std::make_unique<BulletRigid>(Vector3d<float>(50.0f, 5.0f, 50.0f), Vector3d<float>(0.0f, -10.0f, 0.0f), 0.0f);
		world.add(ground.get());
	}
	world.setExternalForce(Vector3d<float>(0, -9.8, 0));

}

void BulletRigidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);

	world.simulate(1.0f/60.0f);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);

	{
		const auto& surfels = rigid1->toSurlfes(0.25f).toPositions();
		//rigid1->
		for (const auto& p : surfels) {
			Crystal::Graphics::Point pt(p, ColorRGBA<float>(1, 0, 0, 1), 10.0f);
			buffer.add(pt);
		}
	}
	{
		const auto& surfels = rigid2->toSurlfes(0.25f).toPositions();
		for (const auto& p : surfels) {
			Crystal::Graphics::Point pt(p, ColorRGBA<float>(1, 0, 0, 1), 10.0f);
			buffer.add(pt);
		}
	}
	{
		const auto& surfels = rigid3->toSurlfes(0.25f).toPositions();
		for (const auto& p : surfels) {
			Crystal::Graphics::Point pt(p, ColorRGBA<float>(1, 0, 0, 1), 10.0f);
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
