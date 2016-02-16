#include "gtest/gtest.h"
#include "../Polygon/ActorObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


TEST(ActorObjectTest, TestToParticle)
{
	ActorObject object;
	object.createJoint(Vector3d<float>(0.0, 0.0, 0.0));
	object.createJoint(Vector3d<float>(1.0, 1.0, 1.0));

}