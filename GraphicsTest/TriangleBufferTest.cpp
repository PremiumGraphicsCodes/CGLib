#include "stdafx.h"

#include "../Graphics/TriangleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(TriangleBufferTest, TestAddPolygon)
{
	const Crystal::Math::Triangle3d<float> t(
		Vector3d<float>(0.0, 0.0, 0.0),
		Vector3d<float>(1.0, 0.0, 0.0),
		Vector3d<float>(1.0, 1.0, 0.0)
		);
	PolygonFactory factory;
	PolygonBuilder builder(t.toCurve3d());
	auto polygon = factory.create(builder);
	TriangleBuffer buffer(factory);
	buffer.add(*polygon);
	EXPECT_EQ(1, buffer.getBlocks().size());
	EXPECT_EQ(3, buffer.getBlocks().front().getIndices().size());
	EXPECT_EQ(9, buffer.getPositions().get().size());
	EXPECT_EQ(9, buffer.getNormals().get().size());
	EXPECT_EQ(9, buffer.getTexCoords().get().size());
}
