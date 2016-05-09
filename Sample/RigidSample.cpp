#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "RigidSample.h"

#include "../Physics/Fluid.h"
#include "../Physics/SPHParticle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Shader/LegacyRenderer.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Graphics/Material.h"
#include "../Graphics/Light.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void RigidSample::setup()
{
	constant = SPHConstant(1000.0f, 1000000.0f, 0.0f, 0.0f, 1.25f);
	{
		Box3d<float> box(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
		auto s = new PolygonObject();
		s->add(box);
		auto r = new BulletRigid(box, &constant, -1, s);
		rigids.push_back(r);
		world.add(r);
	}
	{
		Box3d<float> box(Vector3d<float>(-0.5, 0.5f, -0.5f), Vector3d<float>(0.5f, 1.0f, 0.5f));
		auto s = new PolygonObject();
		s->add(box);
		auto r  = new BulletRigid(box, &constant, -1, s);
		rigids.push_back(r);
		world.add(r);
	}
	{
		Box3d<float> box(Vector3d<float>(-0.5, 1.0f, -0.5f), Vector3d<float>(0.5f, 2.0f, 0.5f));
		auto s = new PolygonObject();
		s->add(box);
		auto r = new BulletRigid(box, &constant, -1, s);
		world.add(r);
	}

	const Box3d<float> box(Vector3d<float>(-50.0f, -5.0f, -50.0f), Vector3d<float>(50.0f, 100.0f, 50.0f));
	world.setBoundary(box);
	world.setExternalForce(Vector3d<float>(0, -9.8f, 0));

	smoothRenderer.build();
}

void RigidSample::cleanup()
{
	for (auto r : rigids) {
		delete r;
	}
	rigids.clear();
	for (auto s : shapes) {
		delete s;
	}
	shapes.clear();
}

void RigidSample::onMiddleButtonDown(const float x, const float y)
{
}


void RigidSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	world.simulate(1.0f/60.0f);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0f, 10.0f, -10.0f));
	light.setDiffuse(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));

	for (auto r : rigids) {
		TriangleBuffer triangleBuffer;
		const auto matrix = r->getTransformMatrix();
		auto p = r->getShape()->clone();
		p->transform(matrix);
		triangleBuffer.add(*p);
		Material material;
		material.setAmbient(ColorRGBA<float>(0.2, 0.2, 0.2, 0.0));
		smoothRenderer.render(camera, triangleBuffer, light, material);
		delete p;
	}
}
