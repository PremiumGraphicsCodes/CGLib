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
		Box<float> box(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
		rigid1 = std::make_unique<BulletRigid>(box, &constant);
		shape1.add(box);
		world.add(rigid1.get());
		rigidPolygonMap[ rigid1.get() ] = &shape1;
	}
	{
		Box<float> box(Vector3d<float>(-0.5, 0.5f, -0.5f), Vector3d<float>(0.5f, 1.0f, 0.5f));
		shape2.add(box);
		rigid2 = std::make_unique<BulletRigid>(box, &constant);
		world.add(rigid2.get());
		rigidPolygonMap[rigid2.get()] = &shape2;
	}
	{
		Box<float> box(Vector3d<float>(-0.5, 1.0f, -0.5f), Vector3d<float>(0.5f, 2.0f, 0.5f));
		shape3.add(box);
		rigid3 = std::make_unique<BulletRigid>(box, &constant);
		world.add(rigid3.get());
		rigidPolygonMap[rigid3.get()] = &shape3;
	}

	const Box<float> box(Vector3d<float>(-50.0f, -5.0f, -50.0f), Vector3d<float>(50.0f, 100.0f, 50.0f));
	world.setBoundary(box);
	world.setExternalForce(Vector3d<float>(0, -9.8f, 0));

	smoothRenderer.build();
}

void RigidSample::onMiddleButtonDown(const float x, const float y)
{
	//const auto xRatio = x / float(this->width);
	//const auto yRatio = y / float(this->height);
	////std::cout << xRatio << std::endl;
	////std::cout << yRatio << std::endl;
	//const auto screenx = fb.getWidth() * xRatio;
	//const auto screeny = fb.getHeight() * yRatio;
	//std::cout << screenx << std::endl;
	//std::cout << screeny << std::endl;
	//const auto c = fb.getColor(screenx, screeny);
	///*
	//std::cout << (float)c.getRed() << std::endl;
	//std::cout << (float)c.getGreen() << std::endl;
	//std::cout << (float)c.getBlue() << std::endl;
	//std::cout << (float)c.getAlpha() << std::endl;
	//*/
	//const int pickedColor = c.getRed();
	//for (auto r : rigids) {
	//	const unsigned int id = r->getId();
	//	if (id == pickedColor) {
	//		selected = r;
	//	}
	//}
}


void RigidSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	world.simulate(1.0f/60.0f);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);

	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0f, 10.0f, -10.0f));
	light.setDiffuse(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));

	for (auto m : rigidPolygonMap) {
		//LineBuffer lineBuffer;
		TriangleBuffer triangleBuffer;
		const auto matrix = m.first->getTransformMatrix();
		auto p = m.second->clone();
		p->transform(matrix);
		//lineBuffer.add(*p);
		triangleBuffer.add(*p);
		//renderer.render(camera, lineBuffer);
		smoothRenderer.render(camera, triangleBuffer);
		delete p;
	}
}
