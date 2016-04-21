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
	onRenderer.build();
	depthRenderer.build();

	cursor = Vector3d<float>(0.0f, 20.0f, 25.0f);

	fluidRenderer.build(512, 512);

	std::cout << "middle button dragg : cursor move" << std::endl;
	std::cout << "press X : add fluid to x+" << std::endl;
	std::cout << "press Z : add fluid to x-" << std::endl;

	isParticleView = false;

	std::array< Crystal::Graphics::Imagef, 6> images;
	images[0].read("../Shader/cube_PX.png");
	images[1].read("../Shader/cube_NX.png");
	images[2].read("../Shader/cube_PY.png");
	images[3].read("../Shader/cube_NY.png");
	images[4].read("../Shader/cube_PZ.png");
	images[5].read("../Shader/cube_NZ.png");


	cubeMapTexture.create(images, 11);

	backgroundBuffer.build(512, 512, 10);
	skyBoxRenderer.build();

}

void FluidSample::onKeyDown(const unsigned char c)
{
	if (c == 'x') {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 5; ++j) {
				//fluids[i]->move(Vector3d<float>(0.25f, 0.0f, 0.0f));
				const auto pos = cursor + Vector3d<float>(i, j, i);
				fluids.front()->createParticle(pos, Vector3d<float>(-50.0f, -20.0f, 0.0f));
			}
		}
	}
	if (c == 'z') {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 5; ++j) {
				const auto pos = cursor + Vector3d<float>(i, j, i);
				fluids.front()->createParticle(pos, Vector3d<float>(50.0f, -20.0f, 0.0f));
			}
		}
	}
	if (c == 'p') {
		isParticleView = !isParticleView;
	}
}

void FluidSample::onMiddleButtonDown(const float x, const float y)
{
}

void FluidSample::onMiddleDragging(const float dx, const float dy)
{
	Vector3d<float> v(-dx*0.1f, dy*0.1f, 0.0f);
	v = v.getMult(rotationMatrix);
	cursor += v;
}


void FluidSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	this->rotationMatrix = camera.getRotationMatrix();

	this->width = width;
	this->height = height;

	const float effectLength = 1.20f;
	world.simulate(effectLength, 0.02f);

	//auto polygon = fluid->toSurfacePolygonObject(500.0f, 1.25f);

	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);

		PointBuffer buffer;
		Point point(cursor, ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 500.0f);
		buffer.add(point);
		renderer.render(camera, buffer);
	}

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

	/*
	float minPressure = +FLT_MAX;
	float maxPressure = -FLT_MAX;
	for (auto p : particles) {
		minPressure = std::min<float>(minPressure, p->getDensity());
		maxPressure = std::max<float>(maxPressure, p->getDensity());
	}
	colorMap.setMinMax(minPressure, maxPressure);
	*/
	colorMap.setMinMax(900, 1400);


	for (auto p : particles) {
		const auto pos = p->getPosition();
		const auto d = p->getDensity();
		auto color = colorMap.getColor(p->getDensity());
		color.setAlpha(0.2f);//colorMap.getNormalized(p->getDensity()));
		Crystal::Graphics::Point point(pos, color, 500.0f, p->getId());
		buffer.add(point);
	}


	if (isParticleView) {
		renderer.render(camera, buffer);
	}
	else {
		glViewport(0, 0, backgroundBuffer.getWidth(), backgroundBuffer.getHeight());
		backgroundBuffer.bind();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skyBoxRenderer.render(cubeMapTexture, camera);
		backgroundBuffer.unbind();


		PointLight<float> light;
		light.setPos(Vector3d<float>(10.0, 0.0, 0.0));
		light.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0, 0.0));
		light.setSpecular(ColorRGBA<float>(1.0, 0.0, 0.0));
		light.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));

		Material material;
		material.setDiffuse(ColorRGBA<float>(1.0, 1.0, 1.0));
		material.setSpecular(ColorRGBA<float>(1.0, 0.0, 0.0));
		material.setAmbient(ColorRGBA<float>(0.5, 0.5, 0.5));
		material.setShininess(1.0f);

		fluidRenderer.setSceneTexture(*backgroundBuffer.getTexture());
		fluidRenderer.render(width, height, camera, buffer, light, material, cubeMapTexture);
	}

	/*
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto depthTexture = fluidRenderer.getBluredTexture1();
	onRenderer.render(*depthTexture, 1.0f);
	*/
}
