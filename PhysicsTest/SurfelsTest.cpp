#include "gtest/gtest.h"

#include "../Physics/Surfels.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(SurfelsTest, TestToPositions)
{
	{
		Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f));
		Surfels surfels(box, 1.0f);
		const auto& actual = surfels.toPositions();
		EXPECT_EQ(8, actual.size());
	}

	{
		Box<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(4.0f, 4.0f, 4.0f));
		Surfels surfels(box, 1.0f);
		const auto& actual = surfels.toPositions();
		EXPECT_EQ(8, actual.size());
	}

}