#include "stdafx.h"
#include "../Core/FaceSpaceHash.h"
#include "../Core/Vertex.h"
#include "../Core/FaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceSpaceHashTest, TestGetNeighbor)
{
	FaceSpaceHash hash(1.0f, 100);
	Vertex v1(Vector3d<float>(0.0f, 0.0f, 0.0f));
	Vertex v2(Vector3d<float>(5.0f, 0.0f, 0.0f));
	Vertex v3(Vector3d<float>(5.0f, 5.0f, 0.0f));

	FaceBuilder builder({ &v1, &v2, &v3 });
	auto f = builder.build(0, 1, 2);

	hash.add(f);
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0)).size());
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(1.0, 1.0, 0.0)).size());

	EXPECT_EQ(0, hash.getNeighbor(Vector3d<float>(10.0, 0.0, 0.0)).size());

	//EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(1.0, 0.0, 0.0), 1.0f).size());
	//EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(-1.0, 0.0, 0.0), 1.0f).size());
}
