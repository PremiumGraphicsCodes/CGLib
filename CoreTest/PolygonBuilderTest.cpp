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

TEST(PolygonBuilderTest, TestCreateTriangles)
{
	Triangle3d<float> triangle1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Triangle3d<float> triangle2 = triangle1;
	std::vector<Triangle3d<float>> triangles;
	triangles.push_back(triangle1);
	triangles.push_back(triangle2);
	PolygonBuilder builder;
	builder.create(triangles, 0.1f);
	EXPECT_EQ(3, builder.getVertices().size());
	EXPECT_EQ(6, builder.getEdges().size());
}


TEST(PolygonBuilderTest, TestFromVolume)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	Volume object(space, grid);
	PolygonBuilder builder(object, 0.5f);
	EXPECT_EQ(4, builder.getVertices().size());
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

TEST(PolygonBuilderTest, TestReverse)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(1, 1, 0));
	std::vector<Vertex*> vertices = { &v1, &v2, &v3 };
	PolygonBuilder builder(vertices);
	auto face = builder.createFace(&v1, &v2, &v3);
	auto polygon = builder.build();
	builder.reverse(face);
}