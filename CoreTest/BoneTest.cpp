#include "gtest/gtest.h"

#include "../Core/Joint.h"
#include "../Core/Bone.h"
#include "../Core/Particle.h"
#include "../Core/AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;


TEST(BoneTest, TestCreateChild)
{
	Joint joint1(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.5);
	Joint joint2(Vector3d<float>(10.0f, 0.0f, 0.0f), 0.5);
	Joint joint3(Vector3d<float>(20.0f, 0.0f, 0.0f), 0.5);
	Bone bone(&joint1, &joint2, 1, 1);
	auto child = bone.createChild(&joint3);
}

TEST(BoneTest, TestGetLength)
{
	Joint joint1(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.5);
	Joint joint2(Vector3d<float>(10.0f, 0.0f, 0.0f), 0.5);
	Bone bone(&joint1, &joint2, 1, 1);
	EXPECT_EQ(10.0f, bone.getLength());
}

TEST(BoneTest, TestToParticles)
{
	Joint joint1(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.5);
	Joint joint2(Vector3d<float>(10.0f, 0.0f, 0.0f), 0.5);
	Bone bone(&joint1, &joint2, 1, 1);
	const auto& actual = bone.toParticles(5.0f, 10.0f);
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(Vector3d<float>(3.0f, 0.0f, 0.0f), actual[0].getPosition());
	EXPECT_EQ(Vector3d<float>(8.0f, 0.0f, 0.0f), actual[1].getPosition());
}

TEST(BoneTest, TestToAnisoParticles)
{
	Joint joint1(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.5);
	Joint joint2(Vector3d<float>(10.0f, 0.0f, 0.0f), 0.5);
	Bone bone(&joint1, &joint2, 1, 1);
	const auto& actual = bone.toAnisoParticles(5.0f, 10.0f);
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(Vector3d<float>(3.0f, 0.0f, 0.0f), actual[0].getPosition());
	EXPECT_EQ(Vector3d<float>(8.0f, 0.0f, 0.0f), actual[1].getPosition());
}