#ifndef __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__
#define __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__

#include "PhysicsObject.h"
#include "SPHKernel.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Box;
	}
	namespace Physics {

class PhysicsWorld
{
public:
	PhysicsWorld();

	void simulate();

private:
	std::vector< PhysicsObject* > objects;
	float effectLength;
	float timeStep;
	Math::Vector3d<float> externalForce;
	SPHKernel<float> kernel;

	Math::Box<float> boundary;

	std::vector<Particle*> getParticles();

	void solveBoundary(const std::vector<Particle*>& particles);

	Math::Vector3d<float> getBoundaryForce(const Math::Vector3d<float>& center);

	Math::Vector3d<float> getForceX(const float x);
	Math::Vector3d<float> getForceY(const float y);
	Math::Vector3d<float> getForceZ(const float z);

	float getForce(const float over);

};

	}
}

#endif
