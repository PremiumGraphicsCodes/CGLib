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
	constant = SPHConstant(1000.0f, 1000000.0f, 0.0f, 0.0f, 1.25f);

	for (int i = 0; i < 10; ++i)
	{
		Box<float> box(Vector3d<float>(-4.0f, 2.0f*i, -2.0f), Vector3d<float>(-2.0f, 2.0f*(i+1), 2.0f));
		auto rigid = new BulletRigid(box, 10.0f, &constant);
		rigid->transform();
		bulletWorld.add(rigid);
		Box<float> localBox(Vector3d<float>(-1.0f, -1.0f, -1.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));

		auto shape = new PolygonObject();
		shape->add(localBox);
		shapes.push_back(shape);
		rigidPolygonMap[rigid] = shape;
		rigids.push_back(rigid);
	}


	{
		Box<float> box3(Vector3d<float>(-50.0f, -50.0f, -50.0f), Vector3d<float>(50.0f, 0.0f, 50.0f));

		ground = std::make_unique<BulletRigid>(box3, 0.0f, &constant);
		bulletWorld.add(ground.get());
	}
	bulletWorld.setExternalForce(Vector3d<float>(0, -9.8, 0));

	{
		SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
		Box<float> box(Vector3d<float>(0.0f, 0.0f, -10.0f), Vector3d<float>(20.0f, 20.0f, 1.0f));
		fluid = std::make_unique<Fluid>(box, 1.0f, constant);
		particleWorld.add(fluid.get());
		particleWorld.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
		Box<float> boundary(Vector3d<float>(-100.0, 0.0f, -20.0), Vector3d<float>(100.0, 1000.0, 20.0));
		particleWorld.setBoundary(boundary);

	}

	interaction = BulletInteraction(&particleWorld, &bulletWorld);
	for (auto r : rigids) {
		interaction.add(r);
	}
}

void BulletInteractionSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	interaction.simulate(1.0f / 60.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;


	for (auto m : rigidPolygonMap) {
		LineBuffer lineBuffer;
		const auto matrix = m.first->getTransformMatrix();
		auto p = m.second->clone();
		p->transform(matrix);
		lineBuffer.add(*p);
		renderer.render(camera, lineBuffer);
		delete p;
	}

	{
		PointBuffer buffer;
		buffer.add(*fluid);
		renderer.renderAlphaBlend(camera, buffer);

	}

}
