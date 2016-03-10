#ifndef __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__
#define __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__

class btDiscreteDynamicsWorld;

#include "BulletParticle.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject;
class btRigidBody;

class ParticleWorld;


class BulletInteraction
{
public:
	BulletInteraction(ParticleWorld* particleWorld, btDiscreteDynamicsWorld* bulletWorld);

	void add(const BulletParticle& bp) { bulletParticles.push_back(bp); }

	void forwardTime(const float timeStep);

	//Particle

private:
	std::vector<BulletParticle> bulletParticles;
	ParticleWorld* particleWorld;
	btDiscreteDynamicsWorld* bulletWorld;
};
	}
}

#endif
