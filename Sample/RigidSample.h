#ifndef __CRYSTAL_SAMPLE_RIGID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RIGID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Rigid.h"
#include "../Physics/PhysicsWorld.h"
#include "ISample.h"
#include <memory>

class RigidSample : public ISample
{
public:
	RigidSample() {}

	void setup() override;

	void demonstrate() override;

	void cleanup() override;

private:
	std::unique_ptr< Crystal::Physics::Rigid> rigid1;
	std::unique_ptr< Crystal::Physics::Rigid> rigid2;
	Crystal::Physics::PhysicsWorld world;
};

#endif