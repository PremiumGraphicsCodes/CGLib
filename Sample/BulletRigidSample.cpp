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
	const Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));

	rigid = std::make_unique<BulletRigid>(box, 1.0f);
	world.getWorld()->addRigidBody(rigid->getBody());
	world.getWorld()->setGravity(btVector3(0, -9.8, 0));
	{
		const Box<float> box(Vector3d<float>(-5.0f, -55.0f, -5.0f), Vector3d<float>(5.0f, -5.0f, 5.0f));
		ground = std::make_unique<BulletRigid>(box, 0.0f);
		world.getWorld()->addRigidBody(ground->getBody());
	}
}

void BulletRigidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);

	world.getWorld()->stepSimulation(0.01f, 10);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	Crystal::Graphics::Point pt(rigid->getOrigin(), ColorRGBA<float>(1,0,0,1), 10.0f);
	buffer.add(pt);
	renderer.render(camera, buffer);

	/*
	LineBuffer buffer;
	buffer.add(*polygon);
	renderer.render(camera, buffer);
	*/
}
