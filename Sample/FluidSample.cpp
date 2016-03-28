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
	SPHConstant constant(1000.0f, 1000000.0f, 10000.0f, 0.0f, 1.25f);
	Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(100.0f, 50.0f, 10.0f));
	fluid = std::make_unique<Fluid>(box, 1.0f, constant);
	world.add(fluid.get());
	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box<float> boundary( Vector3d<float>(-10.0, 0.0f, 0.0 ), Vector3d<float>(100.0, 1000.0, 20.0 ));
	world.setBoundary(boundary);
	std::vector<ColorRGBA<float>> colors;
	for (int i = 0; i < 180; ++i) {
		ColorHSV hsv(i, 1.0f, 1.0f);
		colors.push_back( hsv.toColorRGBA());
	}
	std::reverse(colors.begin(), colors.end());
	colorMap.setColors(colors);
}

void FluidSample::demonstrate(const Crystal::Graphics::ICamera<float>& camera)
{	
	const float effectLength = 1.25f;
	world.simulate(effectLength, 0.015f);

	//auto polygon = fluid->toSurfacePolygonObject(500.0f, 1.25f);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;

	PointBuffer buffer;
	const auto& particles = fluid->getParticles();
	/*
	float minPressure = +DBL_MAX;
	float maxPressure = -DBL_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	*/
	colorMap.setMinMax(800.0f, 2000.0f);
	for (auto p : particles) {
		const auto pos = p->getPosition();
		auto color = colorMap.getColor(p->getDensity());
		//color.setAlpha(colorMap.getNormalized(p->getDensity()));
		Crystal::Graphics::Point point(pos, color, 10.0f);
		buffer.add(point);
	}
	renderer.render(camera, buffer, 100.0f);

	/*
	TriangleBuffer lineBuffer;
	lineBuffer.add(*polygon);
	renderer.render(camera, light, lineBuffer);

	delete polygon;
	*/
}
