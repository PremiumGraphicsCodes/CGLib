#ifndef __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__
#define __CRYSTAL_PHYSICS_PHYSICS_WORLD_H__

#include "PhysicsObject.h"
#include "SPHKernel.h"
#include "../Math/Box.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class PhysicsObject;
		class BulletRigid;

class ParticleWorld
{
public:
	ParticleWorld() {}

	void add(PhysicsObject* object) { objects.push_back(object); }

	void add(BulletRigid* rigid);

	void simulate(const float effectLength, const float timeStep);

	void setBoundary(const Math::Box<float>& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3d<float>& force) { this->externalForce = force; }

	std::vector< SPHParticle*> getAllParticles() const;

	std::vector<SPHParticle*> getFluidParticles() const;

	std::vector< SPHParticle*> getBoundaryParticles() const;


private:
	std::vector< PhysicsObject* > objects;
	Math::Vector3d<float> externalForce;
	SPHKernel<float> kernel;
	Math::Box<float> boundary;
	std::vector<BulletRigid*> bulletRigids;


};

	}
}

#endif
