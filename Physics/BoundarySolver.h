#ifndef __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__

#include "../Math/Box.h"

namespace Crystal {
	namespace Physics {
		class Particle;

class BoundarySolver
{
public:
	BoundarySolver():
	timeStep(1.0f){};

	BoundarySolver(const float timeStep, const Math::Box<float>& boundary);

	void solve(const std::vector<Particle*>& particles);

private:
	Math::Vector3d<float> getBoundaryForce(const Math::Vector3d<float>& center);

	Math::Vector3d<float> getForceX(const float x);
	Math::Vector3d<float> getForceY(const float y);
	Math::Vector3d<float> getForceZ(const float z);

	float getForce(const float over);

	const float timeStep;
	const Math::Box<float> boundary;
};
	}
}

#endif