#ifndef __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__
#define __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__

#include <vector>
#include "BulletRigid.h"
#include "BulletParticle.h"

class btRigidBody;

namespace Crystal {
	namespace Physics {

class SPHParticle;
class PhysicsObject;
class SPHParticlePair;
class BulletRigid;

class BulletBoundary
{
public:
	//BulletBoundary()

	BulletBoundary(const BulletParticle& bp1, const BulletParticle& bp2) :
		bp1(bp1),
		bp2(bp2)
	{}

	std::vector<SPHParticlePair> createPairs();

private:
	BulletParticle bp1;
	BulletParticle bp2;
};

	}
}

#endif