#ifndef __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "ISample.h"
#include <memory>

class FluidSample : public ISample
{
public:
	FluidSample() {}

	void setup() override;

	void demonstrate() override;

	void cleanup() override;
private:
	std::unique_ptr<Crystal::Physics::Fluid> fluid;
	Crystal::Physics::PhysicsWorld world;
};

#endif