#ifndef __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__
#define __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__

#include "PhysicsObject.h"
#include "SPHKernel.h"
#include "../Math/Box.h"
#include <vector>

namespace Crystal {
	namespace Math {
		template<typename>
		class Box;
	}
	namespace Physics {
		class PhysicsObject;

class PhysicsWorld
{
public:
	PhysicsWorld() {}

	void add(PhysicsObject* object) { objects.push_back(object); }

	void simulate(const float effectLength, const float timeStep);

	void setBoundary(const Math::Box<float>& boundary) { this->boundary = boundary; }

private:
	std::vector< PhysicsObject* > objects;
	Math::Vector3d<float> externalForce;
	SPHKernel<float> kernel;
	Math::Box<float> boundary;


	std::vector<Particle*> getParticles();


};

	}
}

#endif
