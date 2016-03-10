#ifndef __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__
#define __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__

class btDiscreteDynamicsWorld;

#include "BulletMap.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject;
class btRigidBody;

class ParticleWorld;


class BulletInteraction
{
public:
	BulletInteraction(ParticleWorld* particleWorld, btDiscreteDynamicsWorld* bulletWorld);

	void forwardTime(const float timeStep);

	//Particle

private:
	BulletMap map;
	ParticleWorld* particleWorld;
	btDiscreteDynamicsWorld* bulletWorld;
};
	}
}

#endif
