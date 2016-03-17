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

	Particle particle( Vector3d<float>( 0.5f, 0.5f, 0.5f), 1.0f, 0.25f);
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

	Particle particle(Vector3d<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.25f);
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

TEST(OctTreeTest, CreateChildrenByLength)
{
	Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(4.0f, 4.0f, 4.0f));
	OctTree tree(space);
	EXPECT_TRUE(tree.isEmpty());

	Particle particle(Vector3d<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.25f);
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

TEST(OctTreeTest, CreateChildrenByNumber256)
{
	Vector3d<float> start(-128.0f, -128.0f, -128.0f);
	Vector3d<float> length(256.0f, 256.0f, 256.0f);
	OctTree tree(Space3d<float>(start, length));
	Particle particle(Vector3d<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.25f);
	tree.add(&particle);
	const auto& children = tree.createChildren(8);//Vector3d<float>(effectLength,effectLength,effectLength));
}