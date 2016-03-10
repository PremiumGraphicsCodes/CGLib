#ifndef __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__
#define __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__

#include <vector>
#include "BulletRigid.h"

class btRigidBody;

namespace Crystal {
	namespace Physics {

class Particle;
class PhysicsObject;
class ParticlePair;


class BulletBoundary
{
public:
	//BulletBoundary()

	BulletBoundary(PhysicsObject* physicsObject, btRigidBody* bulletRigid);

	std::vector<ParticlePair> createPairs();

private:
	PhysicsObject* physicsObject;
	btRigidBody* bulletRigid;
};

	}
}

#endif