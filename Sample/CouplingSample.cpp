#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "CouplingSample.h"

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

void CouplingSample::setup()
{
	idRenderer.build();

	constant = SPHConstant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
	rigidConstant = SPHConstant(1000.0f, 10000.0f, 0.0f, 0.0f, 1.25f);

	rigidConstant.isBoundary = true;

	int nextId = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			const int id = nextId++;
			const Vector3d<float> start(-4.0f, 2.0f*i, 2.0f *j);
			const Vector3d<float> end(-2.0f, 2.0f*(i + 1), 2.0f*(j+1));
			Box3d<float> box(start, end);
			auto rigid = new BulletRigid(box, &rigidConstant, id);
			rigid->transform();
			bulletWorld.add(rigid);

			auto shape = new PolygonObject(id);
			shape->add(rigid->getLocalShape());
			shapes.push_back(shape);
			rigidPolygonMap[rigid] = shape;
			rigids.push_back(rigid);
		}
	}
	selected = nullptr;

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
		Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(20.0f, 20.0f, 10.0f));
		fluid = std::make_unique<Fluid>(box, 1.0f, constant);
		particleWorld.add(fluid.get());

	}
	Box3d<float> boundary(Vector3d<float>(-20.0, 0.0f, 0.0), Vector3d<float>(20.0, 1000.0, 20.0));

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

void CouplingSample::cleanup()
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

void CouplingSample::onMouseMove(const float x, const float y)
{

}

void CouplingSample::onKeyDown(const unsigned char c)
{
}

void CouplingSample::onLeftButtonDown(const float x, const float y)
{
}

void CouplingSample::onLeftDragging(const float dx, const float dy)
{
}

void CouplingSample::onMiddleButtonDown(const float x, const float y)
{
	const auto xRatio = x / float(this->width);
	const auto yRatio = y / float(this->height);
	////std::cout << xRatio << std::endl;
	////std::cout << yRatio << std::endl;
	const auto screenx = fb.getWidth() * xRatio;
	const auto screeny = fb.getHeight() * yRatio;
	//std::cout << screenx << std::endl;
	//std::cout << screeny << std::endl;
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

void CouplingSample::onMiddleButtonUp(const float x, const float y)
{
	selected = nullptr;
}

void CouplingSample::onMiddleDragging(const float dx, const float dy)
{
	if (selected == nullptr) {
		return;
	}
	//const auto invMatrix = rotationMatrix.getInverse();
//	Vector3d<float> v(-dx * 0.1, dy * 0.1, 0.0);
//	v = v * invMatrix;
	Vector3d<float> v(-dx*0.1f, dy*0.1f, 0.0f);
	v = v.getMult(rotationMatrix);
	//cursor += v;

	selected->move(v);
}


void CouplingSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
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

	for (auto m : rigidPolygonMap) {
		const auto matrix = m.first->getTransformMatrix();
		auto p = m.second->clone(m.second->getId());
		p->transform(matrix);

		glViewport(0, 0, width, height);

		TriangleBuffer triangleBuffer;
		triangleBuffer.add(*p);
		//renderer.render(camera, lineBuffer);
		smoothRenderer.render(camera, triangleBuffer, light);

		glViewport(0, 0, fb.getWidth(), fb.getHeight());
		fb.bind();
		idRenderer.render(camera, triangleBuffer);
		fb.unbind();

		delete p;
	}

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto m : rigidPolygonMap) {
		const auto matrix = m.first->getTransformMatrix();
		auto p = m.second->clone(m.second->getId());
		p->transform(matrix);

		glViewport(0, 0, width, height);

		TriangleBuffer triangleBuffer;
		triangleBuffer.add(*p);
		//renderer.render(camera, lineBuffer);
		smoothRenderer.render(camera, triangleBuffer, light);

		//glViewport(0, 0, fb.getWidth(), fb.getHeight());

		delete p;
	}

	/*
	{
		PointBuffer buffer;
		buffer.add(*fluid);
		renderer.renderAlphaBlend(camera, buffer);

	}
	*/
	glViewport(0, 0, width, height);

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
	pointRenderer.render(camera, buffer);

}
