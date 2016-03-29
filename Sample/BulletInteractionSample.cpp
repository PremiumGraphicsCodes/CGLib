#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

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

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			const Vector3d<float> start(-4.0f+10, 2.0f*i+10, 2.0f *j);
			const Vector3d<float> end(-2.0f+10, 2.0f*(i + 1)+10, 2.0f*(j+1));
			Box<float> box(start, end);
			auto rigid = new BulletRigid(box, &rigidConstant);
			rigid->transform();
			bulletWorld.add(rigid);

			auto shape = new PolygonObject();
			shape->add(rigid->getLocalShape());
			shapes.push_back(shape);
			rigidPolygonMap[rigid] = shape;
			rigids.push_back(rigid);
		}
	}

	/*
	{
		const Vector3d<float> start(-10.0f, 0.0f, -10.0f);
		const Vector3d<float> end(-8.0f, 20.0f, 10.0f);
		Box<float> box(start, end);
		auto rigid = new BulletRigid(box, &rigidConstant);
		rigid->transform();
		bulletWorld.add(rigid);
		const auto& localShape = rigid->getLocalShape();//Box<float> localBox(Vector3d<float>(-1.0f, -10.0f, -10.0f), Vector3d<float>(1.0f, 10.0f, 10.0f));

		auto shape = new PolygonObject();
		shape->add(localShape);
		shapes.push_back(shape);
		rigidPolygonMap[rigid] = shape;
		rigids.push_back(rigid);

		selected = rigid;

	}
	*/

	{
		SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
		Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(20.0f, 10.0f, 10.0f));
		fluid = std::make_unique<Fluid>(box, 1.0f, constant);
		particleWorld.add(fluid.get());

	}
	Box<float> boundary(Vector3d<float>(0.0, 0.0f, 0.0), Vector3d<float>(20.0, 1000.0, 20.0));

	interaction = BulletInteraction(&particleWorld, &bulletWorld);
	interaction.setExternalForce(Vector3d<float>(0, -9.8, 0));
	interaction.setBoundary(boundary);
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


	shader.build(Crystal::File("../GLSL/point.vs"), Crystal::File("../GLSL/point.fs"));
	auto pr = new PointRenderer<float>(shader);
	pointRenderer.reset(pr);
	pointRenderer->findLocation();

}

void BulletInteractionSample::cleanup()
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

void BulletInteractionSample::onMouseMove(const float x, const float y)
{
}

void BulletInteractionSample::onKeyDown(const unsigned char c)
{
	if (c == 'x') {
		//selected->addForce(Vector3d<float>(0.1f, 0.0f, 0.0f));
		selected->move(Vector3d<float>(0.1f, 0.0f, 0.0f));
	}
	if (c == 'y') {
		//selected->addForce(Vector3d<float>(0.0f, 0.1f, 0.0f));

		selected->move(Vector3d<float>(0.0f, 0.1f, 0.0f));
	}

}

void BulletInteractionSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{
	glEnable(GL_DEPTH_TEST);

	interaction.simulate(1.0f / 60.0f);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
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
	float minPressure = +FLT_MAX;
	float maxPressure = -FLT_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	colorMap.setMinMax(minPressure, maxPressure);

	//colorMap.setMinMax(800.0f, 2000.0f);
	PointBuffer buffer;
	for (auto p : particles) {
		const auto pos = p->getPosition();
		auto color = colorMap.getColor(p->getDensity());
		color.setAlpha(0.1f);
		Crystal::Graphics::Point point(pos, color, 500.0f);
		buffer.add(point);
	}
	pointRenderer->render(camera, buffer);

}
