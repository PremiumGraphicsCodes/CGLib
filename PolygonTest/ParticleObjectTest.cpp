#include "gtest\gtest.h"
#include "../Polygon/Particle.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/VolumeObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


TEST(ParticleObjectTest, TestGetBoundingBox)
{
	ParticleObject object;
	object.add( Particle( Vector3d<float>(-1.0, -1.0, -1.0), 1.0f, 0.5f) );
	object.add(Particle(Vector3d<float>(1.0, 1.0, 1.0), 1.0f, 0.5f));
	Box<float> expected(Vector3d<float>(-1.5, -1.5, -1.5), Vector3d<float>(1.5, 1.5, 1.5));
	EXPECT_EQ(expected, object.getBoundingBox());
}

TEST(ParticleObjectTest, TestToVolumeBox)
{
	Box<float> box(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 1.0));
	ParticleObject object;
	object.add(box, 0.25f);
	auto actual = object.toVolume(box, 0.5f);
}

TEST(PolygonObjectTest, TestToVolumeSphere)
{
	Sphere<float> sphere1(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
	Sphere<float> sphere2(Vector3d<float>(0.0, 0.5, 0.0), 0.5f);

	ParticleObject object;
	object.add(sphere1, 0.25f);
	object.add(sphere2, 0.25f);
	//auto actual = object.toVolume(box, Index3d(2, 2, 2));
}
