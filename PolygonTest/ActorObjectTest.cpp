#include "gtest/gtest.h"
#include "../Polygon/Actor.h"
#include "../Polygon/ParticleObject.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Polygon;


TEST(ActorObjectTest, TestToParticleObject)
{
	Actor object;
	auto j1 = object.createJoint(Vector3d<float>(0.0, 0.0, 0.0));
	auto j2 = object.createJoint(Vector3d<float>(1.0, 1.0, 1.0));
	object.createBone(j1, j2);
	std::unique_ptr<ParticleObject> particle( object.toParticleObject(0.5f, 1.0f) );
	EXPECT_EQ( 2, particle->getParticles().size() );
	//EXPECT_EQ( 2, particles.)
}