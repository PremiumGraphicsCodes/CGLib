#ifndef __CRYSTAL_PHYSICS_PBSPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_PBSPH_SOLVER_H__

#include <vector>

#include "../Math/Vector3d.h"
#include "../Math/Box3d.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;
		class PBSPHObject;

class PBSPHSolver
{
public:
	PBSPHSolver()
	{}

	explicit PBSPHSolver(const std::vector<PBSPHParticle*>& particles) :
		particles(particles)
	{}

	void add(const PBSPHObject& object);

	void simulate(const float dt, const float effectRadius, const float searchRadius, const int maxIter);

	void setBoundary(const Math::Box3d<float>& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3d<float>& force) { this->externalForce = force; }

private:
	std::vector<PBSPHParticle*> particles;
	Math::Box3d<float> boundary;
	Math::Vector3d<float> externalForce;
};

	}
}

#endif