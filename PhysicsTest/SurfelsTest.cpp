#include "gtest/gtest.h"

#include "../Physics/Surfels.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(SurfelsTest, Test)
{
	Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f));
	Surfels surfels(box, 1.0f);
	const auto& actual = surfels.toPositions();
	EXPECT_EQ(26, actual.size());
}