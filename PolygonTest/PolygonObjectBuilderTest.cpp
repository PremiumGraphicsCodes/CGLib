#include "gtest/gtest.h"

#include "../Polygon/PolygonObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(PolygonObjectBuilderTest, TestToVolume)
{
	PolygonObjectBuilder builder;
	
	Box<float> box(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 1.0));
	ParticleObject object;
	object.add(box, 0.25f);
	builder.toVolume(object);
}