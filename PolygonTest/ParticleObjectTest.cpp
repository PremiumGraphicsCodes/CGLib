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

TEST(ParticleObjectTest, TestCreateIntersection)
{
	std::vector<Vector3d<float>> positions1{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object1(positions1);
	std::vector<Vector3d<float>> positions2{
		Vector3d<float>(1.0, 1.0, 1.0),
		Vector3d<float>(2.0, 2.0, 2.0)
	};
	ParticleObject object2(positions2);
	const auto actual = object1.createIntersection(object2);
	EXPECT_EQ(1, actual->getParticles().size());
}

TEST(ParticleObjectTest, TestCreateSub)
{
	std::vector<Vector3d<float>> positions1{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object1(positions1);
	std::vector<Vector3d<float>> positions2{
		Vector3d<float>(1.0, 1.0, 1.0),
		Vector3d<float>(2.0, 2.0, 2.0)
	};
	ParticleObject object2(positions2);
	auto actual = object1.getSub(object2);
	EXPECT_EQ(1, actual.size());
	EXPECT_EQ(Vector3d<float>(-1.0, -1.0, -1.0), actual[0]->getPosition());
}