#ifndef __CRYSTAL_SAMPLE_BULLET_INTERACTION_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_INTERACTION_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"
#include "../Physics/BulletInteraction.h"

#include "../Physics/Rigid.h"
#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "ISample.h"
#include <memory>

class BulletInteractionSample : public ISample
{
public:
	BulletInteractionSample() {}

	void setup();

	void demonstrate();

private:

	void cleanup() {};

	std::unique_ptr< Crystal::Physics::BulletRigid > rigid;
	std::unique_ptr< Crystal::Physics::BulletRigid > rigid2;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	std::unique_ptr< Crystal::Physics::Fluid > fluid;
	Crystal::Physics::ParticleWorld particleWorld;
	Crystal::Physics::BulletWorld bulletWorld;
	Crystal::Physics::BulletInteraction interaction;
};

#endif