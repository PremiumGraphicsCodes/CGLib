#include "stdafx.h"
#include "../Core/PolygonBuilder.h"
#include "../Core/Vertex.h"
#include "../Core/Volume.h"
#include "../Core/Face.h"
#include "../Core/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonBuilderTest, TestBuild)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(1, 1, 0));
	std::vector<Vertex*> vertices = { &v1, &v2, &v3 };
	PolygonBuilder builder(vertices);
	builder.createFace(&v1, &v2, &v3);
	auto actual = builder.build();
	EXPECT_EQ(1, actual->getFaces().size());
	EXPECT_EQ(3, actual->getVertices().size());
	delete actual;
}

TEST(PolygonBuilderTest, TestClean)
{
	Vertex* v1 = new Vertex(Vector3d<float>(0, 0, 0));
	Vertex* v2 = new Vertex(Vector3d<float>(1, 0, 0));
	Vertex* v3 = new Vertex(Vector3d<float>(1, 1, 0));
	Vertex* v4 = new Vertex(Vector3d<float>(0, 0, 0));
	std::vector<Vertex*> vertices = { v1, v2, v3, v4 };
	PolygonBuilder builder(vertices);
	builder.createFace(v1, v2, v3);
	builder.createFace(v4, v2, v3);
	auto actual = builder.build();
	EXPECT_EQ(2, actual->getFaces().size());
	EXPECT_EQ(4, actual->getVertices().size());
	delete actual;
}