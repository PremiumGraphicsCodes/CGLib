#include "stdafx.h"
#include "FaceCollection.h"
#include "Face.h"
#include "Edge.h"

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
	e1->connect(e2);
	e2->connect(e3);
	e3->connect(e1);
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
	*found = nullptr;
	//faces.remove(*found);
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

std::list<Face*> FaceCollection_::findByEdge(Edge* e) const
{
	std::list<Face*> results;
	for (auto f : faces) {
		if (f->has(e)) {
			results.push_back(f);
		}
	}
	return results;
}

void FaceCollection_::renumber()
{
	nextId = 0;
	for (auto e : faces) {
		e->setId(nextId++);
	}
}

void FaceCollection_::cleaning()
{
	faces.remove(nullptr);
	renumber();
}
