#ifndef __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include <memory>

class FluidSample
{
public:
	FluidSample() {
		setup();
	}

	void setup();

	void demonstrate();
private:
	GLFWwindow* window;
	std::unique_ptr< Crystal::Physics::PhysicsObject> object;
	Crystal::Physics::PhysicsWorld world;
};

#endif