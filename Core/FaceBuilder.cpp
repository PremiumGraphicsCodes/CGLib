#include "stdafx.h"
#include "FaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

FaceBuilder::FaceBuilder(const std::vector<Vertex*>& vertices) :
	vertices(vertices)
{}

FaceBuilder::~FaceBuilder()
{
	clear();
}

Face* FaceBuilder::build(int i1, int i2, int i3)
{
	auto e1 = edges.create(vertices[i1], vertices[i2]);
	auto e2 = edges.create(vertices[i2], vertices[i3]);
	auto e3 = edges.create(vertices[i3], vertices[i1]);
	e1->connect(e2);
	e2->connect(e3);
	e3->connect(e1);
	return faces.create(e1, e2, e3);
}

void FaceBuilder::clear()
{
	edges.clear();
	faces.clear();
}
