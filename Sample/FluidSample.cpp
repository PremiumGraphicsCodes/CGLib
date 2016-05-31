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
#include "../Core/ParticleObject.h"
#include "../Core/PolygonMesh.h"
#include "../Graphics/Light.h"
#include "../Graphics/ColorHSV.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	SPHConstant constant(1000.0f, 1000000.0f, 1000.0f, 0.0f, 1.20f);
}

void FluidSample::setup()
{
	isStop = false;
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

	onRenderer.build();
	depthRenderer.build();

	cursor = Vector3d<float>(0.0f, 20.0f, 25.0f);

	fluidRenderer.build(512, 512);

	std::cout << "middle button dragg : cursor move" << std::endl;
	std::cout << "press X : add fluid to x+" << std::endl;
	std::cout << "press Z : add fluid to x-" << std::endl;

	std::array< Crystal::Graphics::Imagef, 6> images;
	images[0].read("../Shader/cube_PX.png");
	images[1].read("../Shader/cube_NX.png");
	images[2].read("../Shader/cube_PY.png");
	images[3].read("../Shader/cube_NY.png");
	images[4].read("../Shader/cube_PZ.png");
	images[5].read("../Shader/cube_NZ.png");


	cubeMapTexture.create(images, 11);

	backgroundBuffer.build(512, 521);
	backgroundTexture.create(Image(512, 512), 12);
	//backgroundBuffer.setTexture(backgroundTexture);
	skyBoxRenderer.build();

	activeTexture = fluidRenderer.getFluidTexture();
}

void FluidSample::onKeyDown(const unsigned char c)
{
	if (c == 'x') {
		fluids.back()->move(Vector3d<float>(0.2f, 0.0, 0.0));
		/*
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 5; ++j) {
				//fluids[i]->move(Vector3d<float>(0.25f, 0.0f, 0.0f));
				const auto pos = cursor + Vector3d<float>(i, j, i);
				fluids.front()->createParticle(pos, Vector3d<float>(-50.0f, -20.0f, 0.0f));
			}
		}
		*/
	}
	if (c == 'z') {
		fluids.back()->move(Vector3d<float>(0.0f, 0.0f, 0.2f));
		/*
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 5; ++j) {
				const auto pos = cursor + Vector3d<float>(i, j, i);
				fluids.front()->createParticle(pos, Vector3d<float>(50.0f, -20.0f, 0.0f));
			}
		}
		*/
	}
	if (c == 'b') {
		const Vector3d<float> start(0.0f, 20.0, 0.0);
		const Vector3d<float> end(10.0, 30.0, 20.0);
		Box3d<float> box(start, end);
		fluids.back()->createParticles(box, 1.0f);
	}
	if (c == 's') {
		Sphere<float> sphere(Vector3d<float>(5.0f, 25.0f, 20.0f), 10.0f);
		fluids.back()->createParticles(sphere, 1.0f);
	}
	if (c == 'p') {
		isStop = !isStop;
	}
	else if (c == 'q') {
		activeTexture = fluidRenderer.getDepthTexture();
	}
	else if (c == 'w') {
		activeTexture = fluidRenderer.getBluredDepthTexture();
	}
	else if (c == 'e') {
		activeTexture = fluidRenderer.getNormalTexture();
	}
	else if (c == 'r') {
		activeTexture = fluidRenderer.getThicknessTexture();
	}
	else if (c == 't') {
		activeTexture = fluidRenderer.getBluredThicknessTexture();
	}
	else if (c == 'y') {
		activeTexture = fluidRenderer.getVolumeTexture();
	}
	else if (c == 'u') {
		activeTexture = fluidRenderer.getReflectionTexture();
	}
	else if (c == 'i') {
		activeTexture = fluidRenderer.getShadedTexture();
	}
	else if (c == 'o') {
		activeTexture = fluidRenderer.getFluidTexture();
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
	if (!isStop) {
		world.simulate(effectLength, 0.02f);
	}


	PointBuffer buffer;
	const auto& particles = world.getFluidParticles();


	for (auto p : particles) {
		const auto pos = p->getPosition();
		const auto d = p->getDensity();
		Crystal::Graphics::Point point(pos, ColorRGBA<float>(), 500.0f, p->getId());
		buffer.add(point);
	}


	glViewport(0, 0, backgroundBuffer.getWidth(), backgroundBuffer.getHeight());
	backgroundBuffer.setTexture(backgroundTexture);
	backgroundBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	skyBoxRenderer.render(cubeMapTexture, camera);
	backgroundBuffer.unbind();


	PointLight<float> light;
	light.setPos(Vector3d<float>(100.0, 100.0, -100.0));
	light.setDiffuse(ColorRGBA<float>(1.0f, 1.0f, 1.0f));
	light.setSpecular(ColorRGBA<float>(1.0f, 0.1f, 0.1f));
	light.setAmbient(ColorRGBA<float>(0.5f, 0.5f, 0.5f));

	Material material;
	material.setDiffuse(ColorRGBA<float>(1.0f, 1.0f, 1.0f));
	material.setSpecular(ColorRGBA<float>(1.0f, 0.1f, 0.1f));
	material.setAmbient(ColorRGBA<float>(0.5f, 0.5f, 0.5f));
	material.setShininess(0.25f);

	fluidRenderer.setSceneTexture(backgroundTexture);
//	fluidRenderer.render(width, height, camera, buffer, light, material, cubeMapTexture);

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//const auto fluidTexture = fluidRenderer.getFluidTexture();
	//const auto fluidDepthTexture = fluidRenderer.getDepthTexture();
	onRenderer.render(*activeTexture);
}
