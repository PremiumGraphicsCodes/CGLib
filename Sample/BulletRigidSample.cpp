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
	constant = SPHConstant(1000.0f, 1000000.0f, 0.0f, 0.0f, 1.25f);
	{
		Box<float> box(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
		rigid1 = std::make_unique<BulletRigid>(box, 10.0f, &constant);
		shape1.add(box);
		world.add(rigid1.get());
		rigidPolygonMap[ rigid1.get() ] = &shape1;
	}
	{
		Box<float> box(Vector3d<float>(-0.5, 0.5f, -0.5f), Vector3d<float>(0.5f, 1.0f, 0.5f));
		shape2.add(box);
		rigid2 = std::make_unique<BulletRigid>(box, 0.1f, &constant);
		world.add(rigid2.get());
		rigidPolygonMap[rigid2.get()] = &shape2;
	}
	{
		Box<float> box(Vector3d<float>(-0.5, 1.0f, -0.5f), Vector3d<float>(0.5f, 2.0f, 0.5f));
		shape3.add(box);
		rigid3 = std::make_unique<BulletRigid>(box, 0.1f, &constant);
		world.add(rigid3.get());
		rigidPolygonMap[rigid3.get()] = &shape3;
	}


	{
		Box<float> box(Vector3d<float>(-50.0f, -50.0f, -50.0f), Vector3d<float>(50.0f, -5.0f, 50.0f));
		ground = std::make_unique<BulletRigid>(box, 0.0f, &constant);
		world.add(ground.get());
	}
	world.setExternalForce(Vector3d<float>(0, -9.8f, 0));

}

void BulletRigidSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	world.simulate(1.0f/60.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);

	for (auto m : rigidPolygonMap) {
		LineBuffer lineBuffer;
		const auto matrix = m.first->getTransformMatrix();
		auto p = m.second->clone();
		p->transform(matrix);
		lineBuffer.add(*p);
		renderer.render(camera, lineBuffer);
		delete p;
	}
}
