#include "gtest\gtest.h"

#include "../Polygon/OctTree.h"
#include "../Polygon/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(OctTreeTest, CreateChildren)
{
	Space3d<float> space( Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f) );
	OctTree tree(space);
	EXPECT_TRUE( tree.isEmpty() );

	Particle particle( Vector3d<float>( 0.5f, 0.5f, 0.5f), 1.0f, 0.5f);
	tree.add(&particle);

	const auto& actual = tree.createChildren();
	EXPECT_EQ( 8, actual.size() );
}