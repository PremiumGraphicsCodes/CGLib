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
	builder.toVolume(object, {4,4,4});
}

TEST(PolygonObjectBuilderTest, TestToVolumeSphere)
{
	PolygonObjectBuilder builder;

	Sphere<float> sphere(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
	ParticleObject object;
	object.add(sphere, 0.25f);
	builder.toVolume(object, { 4,4,4 });
}