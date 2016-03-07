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
	void demonstrate() override;

	void setup() override;

private:
	std::unique_ptr<Crystal::Physics::Fluid> fluid;
	Crystal::Physics::ParticleWorld world;

};

#endif