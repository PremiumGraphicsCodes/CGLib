#include "stdafx.h"
#include "FaceCollection.h"
#include "Face.h"

using namespace Crystal::Core;

FaceCollection_::FaceCollection_() :
	nextId(0)
{
}

FaceCollection_::~FaceCollection_()
{
	//clear();
}

void FaceCollection_::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	nextId = 0;
}

Face* FaceCollection_::create(Edge* e1, Edge* e2, Edge* e3)
{
	auto f = new Face({ e1,e2,e3 }, nextId++);
	//assert(f->getArea() > 0);
	faces.push_back(f);
	return f;
}

void FaceCollection_::merge(FaceCollection_& rhs)
{
	for (auto n : rhs.faces) {
		n->setId(nextId++);
	}
	faces.insert(faces.end(), rhs.faces.begin(), rhs.faces.end());
	rhs.faces.clear();
}

void FaceCollection_::remove(Face* f)
{
	auto found = std::find(faces.begin(), faces.end(), f);
	delete f;
	faces.remove(*found);
}

Face* FaceCollection_::findById(const int id) const
{
	for (auto e : faces) {
		if (e->getId() == id) {
			return e;
		}
	}
	return nullptr;
}