#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/PBSPHSolver.h"
#include "../Physics/PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(PBSPHSolverTest, Test)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f, 1.25f);
	PBSPHParticle particle1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	//PBSPHParticle particle2(Vector3d<float>(1, 0, 0), 0.5f, &constant);

	std::vector<PBSPHParticle*> particles;
	particles.push_back(&particle1);
	//particles.push_back(&particle2);

	PBSPHSolver solver(particles);
	solver.simulate(1.0e-6, 1.25f);
	std::cout << particle1.getPosition().getX() << std::endl;
	std::cout << particle1.getPosition().getY() << std::endl;
	std::cout << particle1.getPosition().getZ() << std::endl;

}