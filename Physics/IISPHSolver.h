#ifndef __CRYSTAL_PHYSICS_IISPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_IISPH_SOLVER_H__

#include <list>

namespace Crystal {
	namespace Physics {
		class IISPHParticle;

class IISPHSolver
{
public:
	void simulate(const double dt, const double effectRadius);

private:
	std::list<IISPHParticle*> particles;
};
	}
}

#endif