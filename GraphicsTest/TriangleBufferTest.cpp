#include "gtest\gtest.h"

#include "../Graphics/TriangleBuffer.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(TriangleBufferTest, Test)
{
	const Crystal::Math::Triangle<float> t(
		Vector3d<float>(0.0, 0.0, 0.0),
		Vector3d<float>(1.0, 0.0, 0.0),
		Vector3d<float>(1.0, 1.0, 0.0)
		);
	TriangleBuffer buffer;
	buffer.add(t);
}

TEST(TriangleBufferTest, TestAddSurface)
{
	Surface surface();
}