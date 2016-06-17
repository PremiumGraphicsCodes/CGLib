#include "stdafx.h"

#include "../Core/OctTree.h"
#include "../Core/Particle.h"
#include "../Core/AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(OctTreeTest, TestIsNeighborByParticle)
{
	Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f));
	OctTree tree(space);
	{
		Particle particle(Vector3d<float>(0.5, 0.5, 0.5), 0.0f, 0.5);
		EXPECT_TRUE(tree.isNeighbor(&particle));
	}
	{
		Particle particle(Vector3d<float>(-1.0, 0.5, 0.5), 0.0f, 0.5);
		EXPECT_FALSE(tree.isNeighbor(&particle));
	}
}

TEST(OctTreeTest, TestIsNeighborByAnisotoropicParticle)
{
	Space3d<float> space(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(2.0f, 2.0f, 2.0f));
	OctTree tree(space);
	{
		const Ellipsoid<float> e(Vector3d<float>(0.5, 0.5, 0.5), Vector3d<float>(2, 1, 1));
		AnisotoropicParticle particle(e, 0.0f);
		EXPECT_TRUE(tree.isNeighbor(&particle));
	}
	{
		const Ellipsoid<float> e(Vector3d<float>(-1.0, 0.5, 0.5), Vector3d<float>(2, 1, 1));
		AnisotoropicParticle particle(e, 0.0f);
		EXPECT_TRUE(tree.isNeighbor(&particle));
	}
}


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
		const auto& actual = tree.createChildren(2);
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