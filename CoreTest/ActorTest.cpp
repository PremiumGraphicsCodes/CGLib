#include "gtest/gtest.h"
#include "../Core/Actor.h"
#include "../Core/ParticleObject.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(ActorTest, TestIsRoot)
{
	Actor actor;

	auto j1 = actor.createJoint( Vector3d<float>(1.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j2 = actor.createJoint( Vector3d<float>(2.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	actor.createBone(j1, j2, Vector3d<float>(1, 1, 1));
	EXPECT_TRUE(actor.isRoot(j1));
	EXPECT_FALSE(actor.isRoot(j2));
}


TEST(ActorTest, TestRemoveBone)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j3 = actor.createJoint(Vector3d<float>(2.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));

	auto b = actor.createBone(j1, j2, Vector3d<float>(1, 1, 1));
	actor.createBone(j2, j3, Vector3d<float>(1, 1, 1));

	actor.remove(b);
	EXPECT_EQ(3, actor.getJoints().size());
	EXPECT_EQ(1, actor.getBones().size());
}

TEST(ActorTest, TestRemoveJoint)
{
	Actor actor;
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j3 = actor.createJoint(Vector3d<float>(2.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));

	actor.createBone(j1, j2, Vector3d<float>(1, 1, 1));
	actor.createBone(j2, j3, Vector3d<float>(1, 1, 1));

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
	auto j1 = actor.createJoint(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j2 = actor.createJoint(Vector3d<float>(1.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));
	actor.createBone(j1, j2, Vector3d<float>(1, 1, 1));

	actor.remove(j2);
	EXPECT_EQ(1, actor.getJoints().size());
	EXPECT_EQ(0, actor.getBones().size());
}

TEST(ActorTest, TestToParticleObject)
{
	Actor object;
	auto j1 = object.createJoint(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.5, 0.5, 0.5));
	auto j2 = object.createJoint(Vector3d<float>(1.0, 1.0, 1.0), Vector3d<float>(0.5, 0.5, 0.5));
	object.createBone(j1, j2, Vector3d<float>(0.5,0.5, 0.5));
	std::unique_ptr<ParticleObject> particle( object.toParticleObject(1.0f) );
	EXPECT_EQ( 6, particle->getParticles().size() );
	//EXPECT_EQ( 2, particles.)
}