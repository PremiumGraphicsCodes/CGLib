#ifndef __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__
#define __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__

#include "PhysicsObject.h"
#include "SPHKernel.h"

namespace Crystal {
	namespace Physics {

class PhysicsWorld
{
public:
	PhysicsWorld();

	void simulate(const float dt);

private:
	std::vector< PhysicsObject* > objects;
	float effectLength;
	Math::Vector3d<float> externalForce;
	SPHKernel<float> kernel;

	std::vector<Particle*> getParticles();
};

	}
}

#endif
