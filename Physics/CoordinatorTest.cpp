#include "gtest/gtest.h"
 
#include "../Physics/Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


TEST( EulerIntegratorTest, Test )
{
	Particle::Constant constant;
	const auto particle = std::make_shared<Particle>( constant, Vector3d<float>( 0.0, 0.0, 0.0 ) );
	particle->setVelocity(Vector3d<float>(1.0f, 0.0f, 0.0f));
	EulerIntegrator integrator( 2.0f );
	integrator.coordinate({ particle.get() });
	const auto actual = particle->getCenter();
	printf("%lf, %lf, %lf\n", actual.getX(), actual.getY(), actual.getZ());
	EXPECT_EQ(Vector3d<float>(2.0f, 0.0f, 0.0), actual);
}
