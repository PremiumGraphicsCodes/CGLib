#ifndef __CRYSTAL_PHYSICS_PBSPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_PBSPH_SOLVER_H__

#include <vector>

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

		class PBSPHSolver
		{
		public:
			PBSPHSolver(const std::vector<PBSPHParticle*>& particles) :
				particles(particles)
			{}

			void simulate(const float dt, const float effectRadius);

		private:
			std::vector<PBSPHParticle*> particles;
		};
	}
}

#endif