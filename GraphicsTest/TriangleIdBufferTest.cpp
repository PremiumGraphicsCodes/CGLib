#include "stdafx.h"

#include "../Graphics/TriangleIdBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(TriangleIdBufferTest, TestAddPolygon)
{
	const Crystal::Math::Triangle3d<float> t(
		Vector3d<float>(0.0, 0.0, 0.0),
		Vector3d<float>(1.0, 0.0, 0.0),
		Vector3d<float>(1.0, 1.0, 0.0)
	);
	PolygonFactory factory;
	PolygonBuilder builder(t.toCurve3d());
	auto polygon = factory.create(builder);
	TriangleIdBuffer buffer(factory);
	buffer.add(*polygon, 0);
	EXPECT_EQ(1, buffer.getBlocks().size());
	EXPECT_EQ(9, buffer.getPositions().get().size());
}
