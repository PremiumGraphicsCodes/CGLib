#include "gtest/gtest.h"

#include "../Physics/SurfaceBuilder.h"
#include "../Math/Matrix.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

TEST(SurfaceBuilderTest, Test)
{
	Particle particle0(Vector3d<float>(-0.5, 0, 0), 1000.0f, 0.5f);

	Particle particle1( Vector3d<float>(0,0,0), 1000.0f, 0.5f);
	Particle particle2( Vector3d<float>(0.5,0,0), 1000.0f, 0.5f);
	Particle particle3(Vector3d<float>(1, 0, 0), 1000.0f, 0.5f);
	Particle particle4(Vector3d<float>(0.0, 0.5, 0), 1000.0f, 0.5f);


	SurfaceBuilder builder({ &particle0,&particle1, &particle2, &particle3, &particle4 });
	builder.updatePosition(1.0);
	auto particles = builder.getAniParticles();
	Matrix<3,3,float> matrix( particles[0]->matrix.toArray3x3() );
	JacobiSolver<3, 3, float> solver(matrix);
	auto m = solver.solve(1.0e-6);
	
	//builder.a
}