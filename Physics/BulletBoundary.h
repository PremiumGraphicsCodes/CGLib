#ifndef __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__
#define __CRYSTAL_PHYSICS_BULLET_BOUNDARY_H__

#include <vector>

class btRigidBody;

namespace Crystal {
	namespace Physics {

class Particle;
class PhysicsObject;
class ParticlePair;

class BulletRigid
{
public:
	BulletRigid(btRigidBody* body) :
		body(body)
	{}

	std::vector<Particle*> toSurfaceParticles();
private:
	btRigidBody* body;
};

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