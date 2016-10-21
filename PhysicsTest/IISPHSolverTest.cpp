#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../Physics/IISPHSolver.h"
#include "../Physics/IISPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IISPHSolverTest, Test)
{
	SPHConstant constant(1000.0f, 0.0f, 0.0f, 0.0f,1.25f);
	IISPHParticle particle(Vector3d<float>(0, 0, 0), 1.0f, &constant);
	std::list<IISPHParticle*> particles;
	particles.push_back(&particle);
	IISPHSolver solver(particles);
	solver.simulate(0.001, 1.25f);
}