#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/IISPHSolver.h"
#include "../Physics/IISPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IISPHSolverTest, Test)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f,1.25f);
	IISPHParticle particle1(Vector3d<float>(0, 0, 0), 1.0f, &constant);
	IISPHParticle particle2(Vector3d<float>(1, 0, 0), 1.0f, &constant);

	std::list<IISPHParticle*> particles;
	particles.push_back(&particle1);
	particles.push_back(&particle2);

	IISPHSolver solver(particles);
	solver.simulate(0.001, 1.25f);
}