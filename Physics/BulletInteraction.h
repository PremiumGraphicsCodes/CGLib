#ifndef __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__
#define __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__

#include "BulletWorld.h"
#include "BulletParticle.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject;
class btRigidBody;

class ParticleWorld;


class BulletInteraction
{
public:
	BulletInteraction() :
		particleWorld(nullptr),
		bulletWorld(nullptr)
	{}

	BulletInteraction(ParticleWorld* particleWorld, BulletWorld* bulletWorld);

	void add(const BulletParticle& bp) { bulletParticles.push_back(bp); }

	void add(BulletRigid* bulletRigid);

	void simulate(const float timeStep);

	void setExternalForce(const Math::Vector3d<float>& f);

	void setBoundary(const Math::Box<float>& box);
	//Particle

private:
	std::vector<BulletParticle> bulletParticles;
	ParticleWorld* particleWorld;
	BulletWorld* bulletWorld;
};
	}
}

#endif
