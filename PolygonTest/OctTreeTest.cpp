#include "gtest\gtest.h"

#include "../Polygon/OctTree.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(OctTreeTest, CreateChildren)
{
	Space3d<float> space( Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f) );
	OctTree tree;
	EXPECT_TRUE( tree.isEmpty() );
}