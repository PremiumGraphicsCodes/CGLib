#include "gtest/gtest.h"

#include "../Graphics/Surface.h"

#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

/*
TEST(PolygonTest, TestAddLine)
{
	Polygon<T> p;
	p.add(Vector3d<T>(), Vector3d<T>(), ColorRGBA<float>());
	EXPECT_EQ(2, p.getVertices().size());
	EXPECT_EQ(1, p.getEdges().size());
}
*/

TEST(PolygonTest, TestAddTriangle)
{
	Surface<T> p;
	p.add(Triangle<T>());
	EXPECT_EQ(3, p.getVertices().size());
	EXPECT_EQ(3, p.getEdges().size());
}

TEST(PolygonTest, TestAddBox)
{
	Surface<T> p;
	p.add(Box<T>());
	EXPECT_EQ(8, p.getVertices().size());
	EXPECT_EQ(12, p.getEdges().size());
}