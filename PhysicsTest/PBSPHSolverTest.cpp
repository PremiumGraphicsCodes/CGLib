#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/PBSPHSolver.h"
#include "../Physics/PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(PBSPHSolverTest, Test)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f, 2.15f);
	PBSPHParticle particle1(Vector3d<float>(0.0, 0.0, 0), 0.125f, &constant);
	PBSPHParticle particle2(Vector3d<float>(0.0, 1.0, 0), 0.125f, &constant);
//	PBSPHParticle particle3(Vector3d<float>(0, 4.0, 0), 0.5f, &constant);

	std::vector<PBSPHParticle*> particles;
	particles.push_back(&particle1);
	particles.push_back(&particle2);
//	particles.push_back(&particle3);

	PBSPHSolver solver(particles);
	for (int i = 0; i < 100; ++i) {
		solver.simulate(1.0e-3, 2.15f, 2.15, 3);
		//std::cout << particle1.getPosition().getX() << std::endl;
		std::cout << particle2.getPosition().getY() << std::endl;
		//std::cout << particle2.getPosition().getY() << std::endl;
	}
}