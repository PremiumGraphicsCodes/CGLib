#include "stdafx.h"
#include "../Core/Face.h"
#include "../Core/Vertex.h"
#include "../Core/FaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceTest, TestGetArea)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>( 1, 0, 0), 0);
	Vertex v3(Vector3d<float>( 1, 1, 0), 0);

	FaceBuilder builder({ &v1, &v2, &v3 });
	auto f = builder.build(0, 1, 2);
	EXPECT_FLOAT_EQ(1, f->getArea());

	v3.moveTo(Vector3d<float>(1, -2, 0));
	EXPECT_FLOAT_EQ(2, f->getArea());
}

TEST(FaceTest, TestGetOrientation)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>( 1, 0, 0), 0);
	Vertex v3(Vector3d<float>( 1, 1, 0), 0);

	FaceBuilder builder({ &v1, &v2, &v3 });
	auto f = builder.build(0, 1, 2);

	EXPECT_EQ( Orientation::CCW, f->getOrientation(Vector3d<float>(0, 0, 1)));
	EXPECT_EQ( Orientation::CW,  f->getOrientation(Vector3d<float>(0, 0,-1)));

	v3.moveTo(Vector3d<float>(1, -2, 0));
	EXPECT_EQ( Orientation::CW,  f->getOrientation(Vector3d<float>(0, 0, 1)));
	EXPECT_EQ( Orientation::CCW, f->getOrientation(Vector3d<float>(0, 0, -1)));

	EXPECT_EQ( Orientation::None, f->getOrientation(Vector3d<float>(1, 1, 0)));
}

TEST(FaceTest, TestToDegenerate)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 0);
	Vertex v3(Vector3d<float>(1, 1, 0), 0);

	FaceBuilder builder({ &v1, &v2, &v3 });
	auto f = builder.build(0, 1, 2);

	EXPECT_FALSE(f->isDegenerated());
	f->toDegenerate();
	EXPECT_TRUE( f->isDegenerated());
}

TEST(FaceTest, TestFindDouble)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>( 1, 0, 0), 1);
	Vertex v3(Vector3d<float>( 0, 1, 0), 2);
	Vertex v4(Vector3d<float>(-1, 0, 0), 3);
	Vertex v5(Vector3d<float>( 0,-1, 0), 4);
	Vertex v6(Vector3d<float>( 0, 1, 0), 5);

	FaceBuilder builder({ &v1, &v2, &v3, &v4, &v5, &v6 });
	auto f1 = builder.build(0, 1, 2);
	auto f2 = builder.build(3, 4, 5);

	auto actual = f1->findDouble(*f2,1.0e-6f);
	EXPECT_EQ(2, actual.size());
	auto found = actual.find(&v1);
	EXPECT_EQ(&v4, (*found).second);
}

TEST(FaceTest, TestMergeDouble)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 1);
	Vertex v3(Vector3d<float>(0, 1, 0), 2);
	Vertex v4(Vector3d<float>(-1, 0, 0), 3);
	Vertex v5(Vector3d<float>(0, -1, 0), 4);
	Vertex v6(Vector3d<float>(0, 1, 0), 5);

	FaceBuilder builder({ &v1, &v2, &v3, &v4, &v5, &v6 });
	auto f1 = builder.build(0, 1, 2);
	auto f2 = builder.build(3, 4, 5);

	f1->mergeDouble(*f2, 1.0e-6f);
	auto edges = f2->getEdges();
	EXPECT_EQ(&v1, edges.front()->getStart());
	EXPECT_EQ(&v3, edges.back()->getStart());
	//EXPECT_EQ(2, actual.size());
	//auto found = actual.find(&v1);
	//EXPECT_EQ(&v4, (*found).second);
}

TEST(FaceTest, TestReverse)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 1);
	Vertex v3(Vector3d<float>(1, 1, 0), 2);

	FaceBuilder builder({ &v1, &v2, &v3 });
	auto f = builder.build(0, 1, 2);
	f->reverse();
	const auto& edges = f->getEdges();
	EXPECT_EQ(&v1, edges.front()->getStart());
	EXPECT_EQ(&v3, edges.front()->getEnd());
}
