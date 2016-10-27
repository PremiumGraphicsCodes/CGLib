#ifndef __CRYSTAL_PHYSICS_PBSPH_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_PBSPH_BOUNDARY_SOLVER_H__

#include "../Math/Box3d.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

class PBSPHBoundarySolver
{
public:
	PBSPHBoundarySolver() {};

	PBSPHBoundarySolver(const Math::Box3d<float>& boundary);

	void solveDensity(const std::vector<PBSPHParticle*>& particles);

	void solveCorrectPosition(const std::vector<PBSPHParticle*>& particles);

private:
	Math::Vector3d<float> getOverVector(const Math::Vector3d<float>& position);

	float getOverX(const float x);
	float getOverY(const float y);
	float getOverZ(const float z);

	const Math::Box3d<float> boundary;
};
	}
}

#endif