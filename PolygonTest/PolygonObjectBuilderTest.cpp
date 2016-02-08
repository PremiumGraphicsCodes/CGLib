#include "gtest/gtest.h"

#include "../Polygon/PolygonObjectBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(PolygonObjectBuilderTest, TestToVolume)
{
	PolygonObjectBuilder builder;
	
	Box<float> box(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 1.0));
	ParticleObject object(box, 0.5f);
	builder.toVolume(object);
}