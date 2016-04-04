#ifndef __CRYSTAL_PHYSICS_BULLET_WORLD_H__
#define __CRYSTAL_PHYSICS_BULLET_WORLD_H__

#include "Bullet.h"
#include "../Math/Vector3d.h"
#include "../Math/Box.h"

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

	void simulate(const float timeStep);

	btDynamicsWorld* getWorld() { return world; }

	std::vector<BulletRigid*> getRigids() const { return rigids; }

	void setBoundary(const Math::Box3d<float>& box);

private:
	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;
	std::vector< BulletRigid* > rigids;

	btDynamicsWorld* world;
};

	}
}

#endif