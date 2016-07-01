#include "stdafx.h"
#include "FaceCollection.h"
#include "Face.h"

using namespace Crystal::Core;

FaceCollection::FaceCollection() :
	nextId(0)
{
}

FaceCollection::~FaceCollection()
{
	clear();
}

void FaceCollection::clear()
{
	faces.clear();
	nextId = 0;
}

Face* FaceCollection::create(Edge* e1, Edge* e2, Edge* e3)
{
	auto f = new Face({ e1,e2,e3 }, nextId++);
	faces.push_back(f);
	return f;
}
