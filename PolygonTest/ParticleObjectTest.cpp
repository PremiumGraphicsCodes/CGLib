#include "gtest\gtest.h"
#include "../Polygon/ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(ParticleObjectTest, TestGetBoundingBox)
{
	std::vector<Vector3d<float>> positions{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object(positions);
	Box<float> expected(Vector3d<float>(-1.0, -1.0, -1.0), Vector3d<float>(1.0, 1.0, 1.0));
	EXPECT_EQ(expected, object.getBoundingBox());
}