#ifndef __CRYSTAL_PHYSICS_IISPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_IISPH_SOLVER_H__

#include <vector>

namespace Crystal {
	namespace Physics {
		class IISPHParticle;

class IISPHSolver
{
public:
	IISPHSolver(const std::vector<IISPHParticle*>& particles) :
		particles(particles)
	{}

	void simulate(const float dt, const float effectRadius);

private:
	std::vector<IISPHParticle*> particles;
};
	}
}

#endif