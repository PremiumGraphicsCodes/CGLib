#ifndef __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Graphics/ColorMap.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/FrameBuffer.h"
#include "ISample.h"
#include <memory>

class FluidSample : public ISample
{
public:
	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	void setup() override;

	void onKeyDown(const unsigned char c) override;

	void onMiddleButtonDown(const float x, const float y) override;

	void onMiddleButtonUp(const float x, const float y) override {};

	void onMiddleDragging(const float dx, const float dy) override;

private:
	std::vector< std::unique_ptr<Crystal::Physics::Fluid> > fluids;
	int width;
	int height;

	Crystal::Physics::ParticleWorld world;
	Crystal::Graphics::ColorMap colorMap;
	Crystal::Shader::PointRenderer renderer;

	Crystal::Shader::IDRenderer idRenderer;
	Crystal::Shader::FrameBuffer fb;

	std::vector<Crystal::Physics::SPHParticle*> selectedParticles;
};

#endif