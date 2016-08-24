#include "stdafx.h"
#include "../Graphics/LineIdBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(LineIdBufferTest, TestAdd)
{
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));

	LineIdBuffer buffer;
	buffer.add(line, DrawableID(0,0));
	EXPECT_EQ(6, buffer.getPosition().get().size());
}

TEST(LineIdBufferTest, TestAddPolygon)
{
	const Crystal::Math::Triangle3d<float> t(
		Vector3d<float>(0.0, 0.0, 0.0),
		Vector3d<float>(1.0, 0.0, 0.0),
		Vector3d<float>(1.0, 1.0, 0.0)
	);
	PolygonRepository factory;
	PolygonBuilder builder(t.toCurve3d());
	auto polygon = factory.create(builder);
	LineIdBuffer buffer(factory, 0);
	buffer.add(*polygon);
	EXPECT_EQ(9, buffer.getPosition().get().size());
	EXPECT_EQ(12, buffer.getIds().get().size());

}