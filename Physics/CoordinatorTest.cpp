#include "gtest/gtest.h"
 
#include "../Physics/Coordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST( EulerIntegratorTest, Test )
{
	Particle<T>::Constant constant;
	const auto particle = std::make_shared<Particle<T> >( constant, Vector3d<T>( 0.0, 0.0, 0.0 ) );
	particle->setVelocity(Vector3d<T>(1.0f, 0.0f, 0.0f));
	EulerIntegrator integrator( 2.0f );
	integrator.coordinate({ particle });
	const auto actual = particle->getCenter();
	printf("%lf, %lf, %lf\n", actual.getX(), actual.getY(), actual.getZ());
	EXPECT_EQ(Vector3d<T>(2.0f, 0.0f, 0.0), actual);
}
