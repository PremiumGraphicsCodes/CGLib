#include "stdafx.h"
#include "../Graphics/LineBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(LineBufferTest, TestAdd)
{
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));

	LineBuffer buffer;
	buffer.add(line, ColorRGBA<float>::Black());
	EXPECT_EQ(6, buffer.getPosition().get().size());
}

TEST(LineBufferTest, TestAddPolygon)
{
	const Crystal::Math::Triangle3d<float> t(
		Vector3d<float>(0.0, 0.0, 0.0),
		Vector3d<float>(1.0, 0.0, 0.0),
		Vector3d<float>(1.0, 1.0, 0.0)
	);
	PolygonRepository factory;
	PolygonBuilder builder(t.toCurve3d());
	auto polygon = factory.create(builder);
	LineBuffer buffer(factory);
	buffer.add(*polygon);
	EXPECT_EQ(9, buffer.getPosition().get().size());
	EXPECT_EQ(6, buffer.getIds().size());

}