#include "gtest\gtest.h"
#include "../Polygon/Particle.h"
#include "../Polygon/ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(ParticleTest, TestGetBoundingBox)
{
	Particle particle( Vector3d<float>(0.0, 0.0, 0.0), 0.5f );
	Box<float> expected(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
	EXPECT_EQ( expected, particle.getBoundingBox() );
}

TEST(ParticleObjectTest, TestGetBoundingBox)
{
	std::vector<Vector3d<float>> positions{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object(positions, 1.0f);
	Box<float> expected(Vector3d<float>(-1.5, -1.5, -1.5), Vector3d<float>(1.5, 1.5, 1.5));
	EXPECT_EQ(expected, object.getBoundingBox());
}

TEST(ParticleObjectTest, TestCreateUnion)
{
	std::vector<Vector3d<float>> positions1{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object1(positions1, 0.5f);
	std::vector<Vector3d<float>> positions2{
		Vector3d<float>(1.0, 1.0, 1.0),
		Vector3d<float>(2.0, 2.0, 2.0)
	};
	ParticleObject object2(positions2, 0.5f);
	auto actual = object1.createUnion(object2);
	EXPECT_EQ(3, actual->getParticles().size());
	//EXPECT_EQ(Vector3d<float>(-1.0, -1.0, -1.0), actual->getParticles().front()->getPosition());
}


TEST(ParticleObjectTest, TestCreateSub)
{
	std::vector<Vector3d<float>> positions1{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object1(positions1, 1.0f);
	std::vector<Vector3d<float>> positions2{
		Vector3d<float>(1.0, 1.0, 1.0),
		Vector3d<float>(2.0, 2.0, 2.0)
	};
	ParticleObject object2(positions2, 1.0f);
	auto actual = object1.createSub(object2);
	EXPECT_EQ(1, actual->getParticles().size());
	EXPECT_EQ(Vector3d<float>(-1.0, -1.0, -1.0), actual->getParticles().front()->getPosition());
}

TEST(ParticleObjectTest, TestCreateIntersection)
{
	std::vector<Vector3d<float>> positions1{
		Vector3d<float>(-1.0, -1.0, -1.0),
		Vector3d<float>(1.0, 1.0, 1.0)
	};
	ParticleObject object1(positions1, 1.0f);
	std::vector<Vector3d<float>> positions2{
		Vector3d<float>(1.0, 1.0, 1.0),
		Vector3d<float>(2.0, 2.0, 2.0)
	};
	ParticleObject object2(positions2, 1.0f);
	const auto actual = object1.createIntersection(object2);
	EXPECT_EQ(1, actual->getParticles().size());
}

