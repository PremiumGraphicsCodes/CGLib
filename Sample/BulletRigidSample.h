#ifndef __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"

#include "../Physics/Rigid.h"
#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "ISample.h"
#include <memory>

class BulletRigidSample : public ISample
{
public:
	BulletRigidSample() {}

	void setup();

	void demonstrate();

private:

	void cleanup() {};

	std::unique_ptr< Crystal::Physics::BulletRigid > rigid1;
	std::unique_ptr< Crystal::Physics::BulletRigid > rigid2;
	std::unique_ptr< Crystal::Physics::BulletRigid > rigid3;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	Crystal::Physics::BulletWorld world;
};

#endif