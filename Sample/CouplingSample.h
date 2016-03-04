#ifndef __CRYSTAL_SAMPLE_COUPLING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_COUPLING_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Rigid.h"
#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include <memory>

class CouplingSample
{
public:
	CouplingSample() {
		setup();
	}

	void setup();

	void demonstrate();
private:
	GLFWwindow* window;
	std::unique_ptr< Crystal::Physics::Fluid > fluid;
	std::unique_ptr< Crystal::Physics::Rigid > rigid;
	Crystal::Physics::PhysicsWorld world;
};

#endif