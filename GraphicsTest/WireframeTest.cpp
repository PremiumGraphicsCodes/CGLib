#include "gtest/gtest.h"

#include "../Graphics/Wireframe.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(WireframeTest, TestTriangle)
{
	Triangle < float > t;
	Wireframe<float> wf;
	wf.add(t);
	EXPECT_EQ(3, wf.getLines().size());
}

TEST(WireframeTest, TestAddBox)
{
	Box<float> b;
	Wireframe<float> frame;
	frame.add(b);
	EXPECT_EQ(12, frame.getLines().size());
}