#include "gtest/gtest.h"
#include "../Polygon/Actor.h"
#include "../Polygon/ParticleObject.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(ActorTest, TestRemoveBone)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), 0.5);
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), 0.5);
	auto j3 = actor.createJoint(Vector3d<float>(2.0, 1.0, 1.0), 0.5);

	auto b = actor.createBone(j1, j2);
	actor.createBone(j2, j3);

	actor.remove(b);
	EXPECT_EQ(3, actor.getJoints().size());
	EXPECT_EQ(1, actor.getBones().size());
}

TEST(ActorTest, TestRemoveJoint)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), 0.5);
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), 0.5);
	auto j3 = actor.createJoint(Vector3d<float>(2.0, 1.0, 1.0), 0.5);

	actor.createBone(j1, j2);
	actor.createBone(j2, j3);

	actor.remove(j2);

	EXPECT_EQ(2, actor.getJoints().size());
	EXPECT_EQ(1, actor.getBones().size());

	/*
	actor.remove(j3);
	EXPECT_EQ(1, actor.getJoints().size());
	EXPECT_EQ(1, actor.getBones().size());
	*/
}

/*
TEST(ActorTest, TestRemoveJointFront)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), 0.5);
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), 0.5);
	actor.createBone(j1, j2);

	actor.remove(j1);
	EXPECT_EQ(1, actor.getJoints().size());
	EXPECT_EQ(0, actor.getBones().size());
}
*/

TEST(ActorTest, TestRemoveJointBack)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), 0.5);
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), 0.5);
	actor.createBone(j1, j2);

	actor.remove(j2);
	EXPECT_EQ(1, actor.getJoints().size());
	EXPECT_EQ(0, actor.getBones().size());
}

TEST(ActorTest, TestToParticleObject)
{
	Actor object;
	auto j1 = object.createJoint(Vector3d<float>(0.0, 0.0, 0.0), 0.5);
	auto j2 = object.createJoint(Vector3d<float>(1.0, 1.0, 1.0), 0.5);
	object.createBone(j1, j2);
	std::unique_ptr<ParticleObject> particle( object.toParticleObject(0.5f, 1.0f) );
	EXPECT_EQ( 3, particle->getParticles().size() );
	//EXPECT_EQ( 2, particles.)
}