#ifndef __CRYSTAL_PHYSICS_BULLET_WORLD_H__
#define __CRYSTAL_PHYSICS_BULLET_WORLD_H__

#include "Bullet.h"

namespace Crystal {
	namespace Physics {
		class BulletRigid;

class BulletWorld
{
public:
	BulletWorld();

	~BulletWorld() {};

	void add(BulletRigid* rigid);

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