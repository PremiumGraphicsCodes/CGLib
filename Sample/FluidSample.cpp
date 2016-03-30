#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

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
		Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(50.0f, 20.0f, 20.0f));
		fluids.push_back( std::make_unique<Fluid>(box, 1.0f, constant) );
		world.add(fluids.back().get());
		std::cout << fluids.back()->getParticles().size() << std::endl;

	}
	{
		Box<float> box(Vector3d<float>(-50.0f,0.0f, 30.0f), Vector3d<float>(0.0f, 20.0f, 50.0f));
		fluids.push_back(std::make_unique<Fluid>(box, 1.0f, constant));
		world.add(fluids.back().get());
		std::cout << fluids.back()->getParticles().size() << std::endl;

	}



	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box<float> boundary( Vector3d<float>(-50.0, 0.0f, 0.0 ), Vector3d<float>(50.0, 1000.0, 50.0 ));

	world.setBoundary(boundary);
	std::vector<ColorRGBA<float>> colors;
	for (int i = 0; i < 360; ++i) {
		ColorHSV hsv(i, 1.0f, 1.0f);
		colors.push_back( hsv.toColorRGBA());
	}
	std::reverse(colors.begin(), colors.end());
	colorMap.setColors(colors);

	shader.build(Crystal::File("../GLSL/point.vs"), Crystal::File("../GLSL/point.fs"));
	auto pr = new PointRenderer<float>(shader);
	renderer.reset(pr);
	renderer->findLocation();

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
			fluids[i]->move(Vector3d<float>(0.0f, 0.0f, 0.25f));
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

void FluidSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	const float effectLength = 1.20f;
	world.simulate(effectLength, 0.015f);

	//auto polygon = fluid->toSurfacePolygonObject(500.0f, 1.25f);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//LegacyRenderer renderer;

	PointBuffer buffer;
	std::vector<SPHParticle*> particles = world.getFluidParticles();

	/*
	const auto eyePos = camera.getPos();
	std::sort(particles.begin(), particles.end(),
		[eyePos](Particle* p1, Particle* p2) {
		const auto dist1 = p1->getPosition().getDistanceSquared(eyePos);
		const auto dist2 = p2->getPosition().getDistanceSquared(eyePos);
		return dist1 < dist2; }
	);
	*/
	float minPressure = +FLT_MAX;
	float maxPressure = -FLT_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	colorMap.setMinMax(minPressure, maxPressure);
	//colorMap.setMinMax(800.0f, 1200.0f);
	for (auto p : particles) {
		const auto pos = p->getPosition();
		const auto d = p->getDensity();
		auto color = colorMap.getColor(p->getDensity());
		color.setAlpha(0.1f);//colorMap.getNormalized(p->getDensity()));
		Crystal::Graphics::Point point(pos, color, 500.0f);
		buffer.add(point);
	}
	renderer->render(camera, buffer);

	/*
	TriangleBuffer lineBuffer;
	lineBuffer.add(*polygon);
	renderer.render(camera, light, lineBuffer);

	delete polygon;
	*/
}
