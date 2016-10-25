#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/IISPHSolver.h"
#include "../Physics/IISPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IISPHSolverTest, Test)
{
	SPHConstant constant(0.1f, 0.0f, 0.0f, 0.0f,1.00f);
	IISPHParticle particle1(Vector3d<float>(0, 0, 0), 0.25f, &constant);
	IISPHParticle particle2(Vector3d<float>(0, 1.0f, 0), 0.25f, &constant);

	std::vector<IISPHParticle*> particles;
	particles.push_back(&particle1);
	particles.push_back(&particle2);

	IISPHSolver solver(particles);

	for (int i = 0; i < 40; ++i) {
		solver.simulate(0.001f, 1.00f);
		std::cout
			//		<< particle1.getPosition().getX() << std::endl
			<< particle2.getPosition().getY() << std::endl;
	//		<< particle1.getPosition().getZ() << std::endl;

//		std::cout
//			<< particle2.getPosition().getX() << std::endl
//			<< particle2.getPosition().getY() << std::endl
//			<< particle2.getPosition().getZ() << std::endl;
	}
}