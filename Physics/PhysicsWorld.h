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
	PhysicsWorld() {}

	void add(PhysicsObject* object) { objects.push_back(object); }

	void simulate(const float effectLength, const float timeStep);

private:
	std::vector< PhysicsObject* > objects;
	Math::Vector3d<float> externalForce;
	SPHKernel<float> kernel;

	Math::Box<float> boundary;

	std::vector<Particle*> getParticles();

	void solveBoundary(const std::vector<Particle*>& particles, const float timeStep);

	Math::Vector3d<float> getBoundaryForce(const Math::Vector3d<float>& center, const float timeStep);

	Math::Vector3d<float> getForceX(const float x, const float timeStep);
	Math::Vector3d<float> getForceY(const float y, const float timeStep);
	Math::Vector3d<float> getForceZ(const float z, const float timeStep);

	float getForce(const float over, const float timeStep);

};

	}
}

#endif
