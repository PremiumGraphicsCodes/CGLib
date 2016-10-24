#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/IISPHSolver.h"
#include "../Physics/IISPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IISPHSolverTest, Test)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f,1.25f);
	IISPHParticle particle1(Vector3d<float>(0, 0, 0), 0.005f, &constant);
//	IISPHParticle particle2(Vector3d<float>(1, 0, 0), 0.005f, &constant);

	std::list<IISPHParticle*> particles;
	particles.push_back(&particle1);
//	particles.push_back(&particle2);

	IISPHSolver solver(particles);
	solver.simulate(1, 1.25f);
	std::cout
		<< particle1.getPosition().getX() << std::endl
		<< particle1.getPosition().getY() << std::endl
		<< particle1.getPosition().getZ() << std::endl;

}