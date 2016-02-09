#include "gtest/gtest.h"

#include "../Polygon/Joint.h"
#include "../Polygon/Bone.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(BoneTest, TestGetLength)
{
	Joint joint1(Vector3d<float>(0.0f, 0.0f, 0.0f), 1.0f, 10.0f);
	Joint joint2(Vector3d<float>(10.0f, 0.0f, 0.0f), 1.0f, 10.0f);
	Bone bone(&joint1, &joint2);
	EXPECT_EQ(10.0f, bone.getLength());
}