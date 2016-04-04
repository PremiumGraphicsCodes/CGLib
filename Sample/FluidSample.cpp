#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "FluidSample.h"

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

void FluidSample::setup()
{
	SPHConstant constant(1000.0f, 1000000.0f, 1000.0f, 0.0f, 1.20f);

	{
		Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(50.0f, 20.0f, 20.0f));
		fluids.push_back( std::make_unique<Fluid>(box, 1.0f, constant) );
		world.add(fluids.back().get());
		std::cout << fluids.back()->getParticles().size() << std::endl;

	}
	{
		Box3d<float> box(Vector3d<float>(-50.0f,0.0f, 30.0f), Vector3d<float>(0.0f, 20.0f, 50.0f));
		fluids.push_back(std::make_unique<Fluid>(box, 1.0f, constant));
		world.add(fluids.back().get());
		std::cout << fluids.back()->getParticles().size() << std::endl;

	}

	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box3d<float> boundary( Vector3d<float>(-50.0, 0.0f, 0.0 ), Vector3d<float>(50.0, 1000.0, 50.0 ));

	world.setBoundary(boundary);
	std::vector<ColorRGBA<float>> colors;
	for (int i = 0; i < 360; ++i) {
		ColorHSV hsv(i, 1.0f, 1.0f);
		colors.push_back( hsv.toColorRGBA());
	}
	std::reverse(colors.begin(), colors.end());
	colorMap.setColors(colors);

	renderer.build();

	idRenderer.build();
	fb.build(512, 512);

}

void FluidSample::onKeyDown(const unsigned char c)
{
	if (c == 'x') {
		for (int i = 0; i < fluids.size(); ++i) {
			fluids[i]->move(Vector3d<float>(0.25f, 0.0f, 0.0f));
		}
	}
	if (c == 'y') {
		for (int i = 0; i < fluids.size(); ++i) {
			fluids[i]->move(Vector3d<float>(0.0f, 0.25f, 0.0f));
		}
	}
	if (c == 'z') {
		for (int i = 0; i < fluids.size(); ++i) {
			fluids[i]->move(Vector3d<float>(0.0f, 0.0f, -0.25f));
		}
	}
	/*
	if (c == 'a') {
		SPHConstant constant(1000.0f, 1000000.0f, 1000.0f, 0.0f, 1.25f);

		Sphere<float> sphere(Vector3d<float>(-10.0f, 20.0f, 20.0f), 10.0f);
		fluids.push_back(std::make_unique<Fluid>(sphere, 1.0f, constant));
		world.add(fluids.back().get());
		std::cout << fluids.back()->getParticles().size() << std::endl;
	}
	*/
}

void FluidSample::onMiddleButtonDown(const float x, const float y)
{

	std::cout << "TEST" << std::endl;
	//selectedParticles.clear();


	const auto xRatio = x / float(this->width);
	const auto yRatio = y / float(this->height);
	//std::cout << xRatio << std::endl;
	////std::cout << yRatio << std::endl;
	const auto screenx = fb.getWidth() * xRatio;
	const auto screeny = fb.getHeight() * yRatio;
	//std::cout << screenx << std::endl;
	//std::cout << screeny << std::endl;
	const auto c = fb.getColor(screenx, fb.getHeight() - screeny);
	std::cout << (float)c.getRed() << std::endl;
}

void FluidSample::onMiddleDragging(const float dx, const float dy)
{
	for (int i = 0; i < 10; ++i) {
		fluids.front()->createParticle(Vector3d<float>(i, 20.0f, 25.0f + i), Vector3d<float>(50.0f, -20.0f, 0.0f));
	}

	//const auto invMatrix = rotationMatrix.getInverse();
	//Vector3d<float> v(dx * 0.1, dy * 0.1, 0.0);
	//v = v * invMatrix;
	/*
	for (auto p : selectedParticles) {
		p->setVelocity(Vector3d<float>(dx*0.01 / 0.015, dy*0.01 / 0.015, 0.0f));
		p->move(Vector3d<float>(dx*0.01, dy*0.01, 0.0f));
	}
	*/
}


void FluidSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	this->width = width;
	this->height = height;

	const float effectLength = 1.20f;
	world.simulate(effectLength, 0.015f);

	//auto polygon = fluid->toSurfacePolygonObject(500.0f, 1.25f);


	//LegacyRenderer renderer;


	PointBuffer buffer;
	std::vector<SPHParticle*> particles = world.getFluidParticles();

	float minPressure = +FLT_MAX;
	float maxPressure = -FLT_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	colorMap.setMinMax(minPressure, maxPressure);

	for (auto p : particles) {
		const auto pos = p->getPosition();
		const auto d = p->getDensity();
		auto color = colorMap.getColor(p->getDensity());
		color.setAlpha(0.2f);//colorMap.getNormalized(p->getDensity()));
		Crystal::Graphics::Point point(pos, color, 500.0f, p->getId());
		buffer.add(point);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, fb.getWidth(), fb.getHeight());
	fb.bind();
	idRenderer.render(camera, buffer);
	fb.unbind();

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);
	renderer.render(camera, buffer);

	/*
	const auto eyePos = camera.getPos();
	std::sort(particles.begin(), particles.end(),
		[eyePos](Particle* p1, Particle* p2) {
		const auto dist1 = p1->getPosition().getDistanceSquared(eyePos);
		const auto dist2 = p2->getPosition().getDistanceSquared(eyePos);
		return dist1 < dist2; }
	);
	*/


	/*
	TriangleBuffer lineBuffer;
	lineBuffer.add(*polygon);
	renderer.render(camera, light, lineBuffer);

	delete polygon;
	*/
}
