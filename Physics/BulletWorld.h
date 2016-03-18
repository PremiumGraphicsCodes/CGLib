#ifndef __CRYSTAL_PHYSICS_BULLET_WORLD_H__
#define __CRYSTAL_PHYSICS_BULLET_WORLD_H__

#include "Bullet.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Physics {
		class BulletRigid;

class BulletWorld
{
public:
	BulletWorld();

	~BulletWorld() {};

	void add(BulletRigid* rigid);

	void setExternalForce(const Math::Vector3d<float>& force);

	void simulate(const float timeStep) { world->stepSimulation(timeStep, 10); }

	btDynamicsWorld* getWorld() { return world; }

private:
	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;

	btDynamicsWorld* world;
};

	}
}

#endif