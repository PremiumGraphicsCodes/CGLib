#ifndef __CRYSTAL_SAMPLE_RIGID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RIGID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Rigid.h"
#include "../Physics/PhysicsWorld.h"
#include <memory>

class RigidSample
{
public:
	RigidSample() {
		setup();
	}

	void setup();

	void demonstrate();
private:
	GLFWwindow* window;
	std::unique_ptr< Crystal::Physics::Rigid> rigid1;
	std::unique_ptr< Crystal::Physics::Rigid> rigid2;
	Crystal::Physics::PhysicsWorld world;
};

#endif