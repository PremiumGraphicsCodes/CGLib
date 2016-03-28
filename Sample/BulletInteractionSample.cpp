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
#include "../Graphics/ColorHSV.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void BulletInteractionSample::setup()
{
	constant = SPHConstant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
	rigidConstant = SPHConstant(1000.0f, 10000.0f, 0.0f, 0.0f, 1.25f);

	rigidConstant.isBoundary = true;

	/*
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			const Vector3d<float> start(-4.0f, 2.0f*i, 2.0f *j);
			const Vector3d<float> end(-2.0f, 2.0f*(i + 1), 2.0f*(j+1));
			Box<float> box(start, end);
			auto rigid = new BulletRigid(box, &rigidConstant);
			rigid->transform();
			bulletWorld.add(rigid);
			Box<float> localBox(Vector3d<float>(-1.0f, -1.0f, -1.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));

			auto shape = new PolygonObject();
			shape->add(localBox);
			shapes.push_back(shape);
			rigidPolygonMap[rigid] = shape;
			rigids.push_back(rigid);
		}
	}
	*/

	{
		const Vector3d<float> start(-10.0f, 0.0f, -10.0f);
		const Vector3d<float> end(-8.0f, 20.0f, 10.0f);
		Box<float> box(start, end);
		auto rigid = new BulletRigid(box, &rigidConstant);
		rigid->transform();
		bulletWorld.add(rigid);
		Box<float> localBox(Vector3d<float>(-1.0f, -10.0f, -10.0f), Vector3d<float>(1.0f, 10.0f, 10.0f));

		auto shape = new PolygonObject();
		shape->add(localBox);
		shapes.push_back(shape);
		rigidPolygonMap[rigid] = shape;
		rigids.push_back(rigid);

	}


	{
		Box<float> box(Vector3d<float>(-50.0f, -50.0f, -50.0f), Vector3d<float>(50.0f, 0.0f, 50.0f));
		ground = std::make_unique<BulletRigid>(box, &constant, true);
		bulletWorld.add(ground.get());
	}
	bulletWorld.setExternalForce(Vector3d<float>(0, -9.8, 0));

	{
		SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
		Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(100.0f, 10.0f, 10.0f));
		fluid = std::make_unique<Fluid>(box, 1.0f, constant);
		particleWorld.add(fluid.get());
		particleWorld.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
		Box<float> boundary(Vector3d<float>(-100.0, 0.0f, 0.0), Vector3d<float>(100.0, 1000.0, 100.0));
		particleWorld.setBoundary(boundary);

	}

	interaction = BulletInteraction(&particleWorld, &bulletWorld);
	for (auto r : rigids) {
		interaction.add(r);
	}

	std::vector<ColorRGBA<float>> colors;
	for (int i = 0; i < 180; ++i) {
		ColorHSV hsv(i, 1.0f, 1.0f);
		colors.push_back(hsv.toColorRGBA());
	}
	std::reverse(colors.begin(), colors.end());
	colorMap.setColors(colors);

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

	/*
	{
		PointBuffer buffer;
		buffer.add(*fluid);
		renderer.renderAlphaBlend(camera, buffer);

	}
	*/
	const auto& particles = fluid->getParticles();
	colorMap.setMinMax(800.0f, 2000.0f);
	PointBuffer buffer;
	for (auto p : particles) {
		const auto pos = p->getPosition();
		auto color = colorMap.getColor(p->getDensity());
		//color.setAlpha(colorMap.getNormalized(p->getDensity()));
		Crystal::Graphics::Point point(pos, color, 10.0f);
		buffer.add(point);
	}
	renderer.render(camera, buffer, 100.0f);

}
