#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "DamBreakSample.h"

#include "../Physics/Fluid.h"
#include "../Physics/SPHParticle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Shader/LegacyRenderer.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/PolygonMesh.h"
#include "../Graphics/Material.h"
#include "../Graphics/Light.h"
#include "../Graphics/ColorHSV.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void DamBreakSample::setup()
{
	idRenderer.build();

	constant = SPHConstant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
	rigidConstant = SPHConstant(10000.0f, 10000.0f, 0.0f, 0.0f, 1.25f);

	rigidConstant.isBoundary = true;

	int nextId = 0;
	for (int i = 0; i < 5; ++i) {
		for (int k = 0; k < 10; ++k) {
			const int id = nextId++;
			const Vector3d<float> start(-4.0f, 2.0f*i, 2.0f *k);
			const Vector3d<float> end(-2.0f, 2.0f*(i + 1), 2.0f*(k + 1));
			Box3d<float> box(start, end);
			auto shape = new PolygonMesh(id);
			auto rigid = new BulletRigid(box, &rigidConstant, id, shape);
			bulletWorld.add(rigid);
			shape->add(rigid->getLocalShape());

			shapes.push_back(shape);
			rigids.push_back(rigid);
		}
	}

	/*
	for (int i = 0; i < 5; ++i) {
	const int id = nextId++;
	const Vector3d<float> start(-4.0f, 10.0f*i, 6.0f);
	const Vector3d<float> end(-2.0f, 10.0f*(i + 1), 8.0f);
	Box3d<float> box(start, end);

	auto shape = new PolygonObject(id);
	auto rigid = new BulletRigid(box, &rigidConstant, id, shape);
	bulletWorld.add(rigid);
	shape->add(rigid->getLocalShape());

	shapes.push_back(shape);
	rigids.push_back(rigid);
	}
	*/


	selected = nullptr;


	{
		SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
		Box3d<float> box(Vector3d<float>(50.0f, 0.0f, 0.0f), Vector3d<float>(100.0f, 10.0f, 10.0f));
		fluid = std::make_unique<Fluid>(box, 1.0f, constant);
		particleWorld.add(fluid.get());

	}
	Box3d<float> boundary(Vector3d<float>(-100.0, 0.0f, 0.0), Vector3d<float>(100.0, 1000.0, 20.0));

	interaction = BulletInteraction(&particleWorld, &bulletWorld);
	interaction.setExternalForce(Vector3d<float>(0, -9.8f, 0));
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


	pointRenderer.build();

	fb.build(512, 512);
	smoothRenderer.build();
}

void DamBreakSample::cleanup()
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

void DamBreakSample::onMouseMove(const float x, const float y)
{

}

void DamBreakSample::onKeyDown(const unsigned char c)
{
	if (c == 'b') {
		const Vector3d<float> start(50.0f, 20.0, 0.0);
		const Vector3d<float> end(100.0, 30.0, 10.0);
		Box3d<float> box(start, end);
		fluid->createParticles(box, 1.0f);
	}
	if (c == 's') {
		Sphere<float> sphere(Vector3d<float>(5.0f, 25.0f, 5.0f), 5.0f);
		fluid->createParticles(sphere, 1.0f);
	}
	if (c == 'r') {
		const Vector3d<float> start(0.0f, 20.0, 0.0);
		const Vector3d<float> end(2.0, 30.0, 10.0);
		Box3d<float> box(start, end);

		auto shape = new PolygonMesh(-1);
		auto rigid = new BulletRigid(box, &rigidConstant, -1, shape);
		bulletWorld.add(rigid);
		shape->add(rigid->getLocalShape());

		shapes.push_back(shape);
		rigids.push_back(rigid);
		interaction.add(rigid);
	}

	std::cout << fluid->getParticles().size() << std::endl;
}

void DamBreakSample::onLeftButtonDown(const float x, const float y)
{
}

void DamBreakSample::onLeftDragging(const float dx, const float dy)
{
}

void DamBreakSample::onMiddleButtonDown(const float x, const float y)
{
	const auto xRatio = x / float(this->width);
	const auto yRatio = y / float(this->height);
	const auto screenx = fb.getWidth() * xRatio;
	const auto screeny = fb.getHeight() * yRatio;
	const auto c = fb.getColor(screenx, fb.getHeight() - screeny);
	///*
	std::cout << (float)c.getRed() << std::endl;
	std::cout << (float)c.getGreen() << std::endl;
	std::cout << (float)c.getBlue() << std::endl;
	std::cout << (float)c.getAlpha() << std::endl;
	const int pickedColor = c.getRed();
	for (auto r : rigids) {
		const unsigned int id = r->getId();
		if (id == pickedColor) {
			selected = r;
		}
	}
}

void DamBreakSample::onMiddleButtonUp(const float x, const float y)
{
	selected = nullptr;
}

void DamBreakSample::onMiddleDragging(const float dx, const float dy)
{
	if (selected == nullptr) {
		return;
	}
	Vector3d<float> v(-dx*0.1f, dy*0.1f, 0.0f);
	v = v.getMult(rotationMatrix);
	//cursor += v;

	selected->setVelocity(v / (1.0f / 60.0f));
	selected->move(v);
}


void DamBreakSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	this->width = width;
	this->height = height;
	this->rotationMatrix = camera.getRotationMatrix();
	glEnable(GL_DEPTH_TEST);

	interaction.simulate(1.0f / 60.0f);


	PointLight<float> light;
	light.setPos(Vector3d<float>(10.0f, 10.0f, -10.0f));
	light.setDiffuse(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto r : rigids) {
		const auto matrix = r->getTransformMatrix();
		auto p = r->getShape()->clone(r->getShape()->getId());
		p->transform(matrix);

		glViewport(0, 0, width, height);

		TriangleBuffer triangleBuffer;
		triangleBuffer.add(*p);
		//renderer.render(camera, lineBuffer);
		Material material;
		material.setAmbient(ColorRGBA<float>(0.2, 0.2, 0.2, 0.0));
		smoothRenderer.render(camera, triangleBuffer, light, material);

		glViewport(0, 0, fb.getWidth(), fb.getHeight());
		fb.bind();
		idRenderer.render(camera, triangleBuffer);
		fb.unbind();

		delete p;
	}

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto r : rigids) {
		const auto matrix = r->getTransformMatrix();
		auto p = r->getShape()->clone(r->getShape()->getId());
		p->transform(matrix);

		glViewport(0, 0, width, height);

		TriangleBuffer triangleBuffer;
		triangleBuffer.add(*p);
		//renderer.render(camera, lineBuffer);
		Material material;
		smoothRenderer.render(camera, triangleBuffer, light, material);

		//glViewport(0, 0, fb.getWidth(), fb.getHeight());

		delete p;
	}

	glViewport(0, 0, width, height);

	const auto& particles = fluid->getParticles();
	float minPressure = +FLT_MAX;
	float maxPressure = -FLT_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	colorMap.setMinMax(900.0f, 1400.0f);

	//colorMap.setMinMax(800.0f, 2000.0f);
	PointBuffer buffer;
	for (auto p : particles) {
		const auto pos = p->getPosition();
		auto color = colorMap.getColor(p->getDensity());
		color.setAlpha(0.5f);
		Crystal::Graphics::Point point(pos, color, 500.0f);
		buffer.add(point);
	}
	pointRenderer.render(camera, buffer);

}
