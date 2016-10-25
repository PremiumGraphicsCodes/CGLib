#ifndef __CRYSTAL_PHYSICS_IISPH_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_IISPH_BOUNDARY_SOLVER_H__

#include "../Math/Box3d.h"

namespace Crystal {
	namespace Physics {
		class IISPHParticle;

class IISPHBoundarySolver
{
public:
	IISPHBoundarySolver() :
		timeStep(1.0f) {};

	IISPHBoundarySolver(const float timeStep, const Math::Box3d<float>& boundary);

	void solve(const std::vector<IISPHParticle*>& particles);

private:
	Math::Vector3d<float> getBoundaryForce(const Math::Vector3d<float>& center);

	Math::Vector3d<float> getForceX(const float x);
	Math::Vector3d<float> getForceY(const float y);
	Math::Vector3d<float> getForceZ(const float z);

	float getForce(const float over);

	const float timeStep;
	const Math::Box3d<float> boundary;
};
	}
}

#endif