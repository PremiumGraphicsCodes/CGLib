#include "gtest\gtest.h"
#include "../Polygon/Particle.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


TEST(ParticleObjectTest, TestGetBoundingBox)
{
	ParticleObject object;
	object.add( Particle( Vector3d<float>(-1.0, -1.0, -1.0), 1.0f, 0.5f) );
	object.add(Particle(Vector3d<float>(1.0, 1.0, 1.0), 1.0f, 0.5f));
	Box3d<float> expected(Vector3d<float>(-1.5, -1.5, -1.5), Vector3d<float>(1.5, 1.5, 1.5));
	EXPECT_EQ(expected, object.getBoundingBox());
}
