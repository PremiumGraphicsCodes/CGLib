#include "gtest/gtest.h"

#include "../Polygon/PolygonObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(PolygonObjectBuilderTest, TestToVolumeBox)
{
	PolygonObjectBuilder builder;
	
	Box<float> box(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 1.0));
	ParticleObject object;
	object.add(box, 0.25f);
	auto actual = builder.toVolume(object, 100);
}

TEST(PolygonObjectBuilderTest, TestToVolumeSphere)
{
	PolygonObjectBuilder builder;

	Sphere<float> sphere1(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
	Sphere<float> sphere2(Vector3d<float>(0.0, 0.5, 0.0), 0.5f);

	ParticleObject object;
	object.add(sphere1, 0.25f);
	object.add(sphere2, 0.25f);
	auto actual = builder.toVolume(object, 100);
}