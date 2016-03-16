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
	EXPECT_FALSE( tree.isEmpty() );

	const auto& actual = tree.createChildren();
	EXPECT_EQ( 1, actual.size() );

	{
		Space3d<float> s(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
		OctTree expected(s);
		expected.add(&particle);
		EXPECT_EQ(expected, actual.front());
	}
}

TEST(OctTreeTest, CreateChildrenByDepth)
{
	Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(4.0f, 4.0f, 4.0f));
	OctTree tree(space);
	EXPECT_TRUE(tree.isEmpty());

	Particle particle(Vector3d<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.5f);
	tree.add(&particle);
	EXPECT_FALSE(tree.isEmpty());

	const auto& actual = tree.createChildren(2);
	EXPECT_EQ(1, actual.size());
}

TEST(OctTreeTest, CreateChildrenByLength)
{
	Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(4.0f, 4.0f, 4.0f));
	OctTree tree(space);
	EXPECT_TRUE(tree.isEmpty());

	Particle particle(Vector3d<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.5f);
	tree.add(&particle);
	EXPECT_FALSE(tree.isEmpty());


	{
		const auto& actual = tree.createChildren(Vector3d<float>(1.0f, 1.0f, 1.0f));
		EXPECT_EQ(1, actual.size());
		Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
		OctTree expected(space);
		expected.add(&particle);
		EXPECT_EQ(expected, actual.front());
	}
}
