#ifndef __CRYSTAL_PHYSICS_BULLET_RIGID_H__
#define __CRYSTAL_PHYSICS_BULLET_RIGID_H__

#include <vector>

class btRigidBody;

namespace Crystal {
	namespace Physics {
		class Particle;

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

	}
}

#endif