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
	std::vector<SPHParticle*> particles;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 10; ++k) {
				Vector3d<float> pos(i * 1.0f, j * 1.0f, k * 1.0f);
				SPHParticle* p = new SPHParticle(pos, 0.5f, 1000.0f, 1000.0f, 100.0f);
				particles.push_back(p);
			}
		}
	}
	fluid = std::make_unique<Fluid>(particles);
	world.add(fluid.get());
	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box<float> boundary( Vector3d<float>(-20.0, 0.0f, 0.0 ), Vector3d<float>(20.0, 100.0, 10.0 ));
	world.setBoundary(boundary);
}

void FluidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	
	const float effectLength = 1.25f;
	world.simulate(effectLength, 0.5f);

	//ParticleObject particleObject;
	//particleObject.add()

	Box<float> boundary(Vector3d<float>(-21.0, -1.0f, -2.0), Vector3d<float>(21.0, 20.0, 12.0));

	std::unique_ptr<PolygonObject> polygon(fluid->toPolygonObject(boundary, 200.0f, effectLength) );

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, -5.0, -20.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	/*
	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(*fluid);
	renderer.render(camera, buffer, 10.0f);
	*/
	PointLight<float> light;
	light.setPos(Vector3d <float>(-10.0, -10.0, 10.0));
	light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));
	//light.setSpecular(ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));

	/*
	TriangleBuffer buffer;
	buffer.add(*polygon);
	renderer.render(camera, light, buffer);
	*/
	LineBuffer buffer;
	buffer.add(*polygon);
	renderer.render(camera, buffer);
}
