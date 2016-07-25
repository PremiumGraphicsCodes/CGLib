#include "stdafx.h"
#include "FaceCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

FaceCollection::FaceCollection() :
	nextId(0)
{}

FaceCollection::FaceCollection(const std::vector<Face*>& faces) :
	nextId(0),
	faces(faces.begin(), faces.end())
{
}


FaceCollection::FaceCollection(const std::list<Face*>& faces) :
	faces(faces),
	nextId(0)
{}

FaceCollection::~FaceCollection()
{
}

void FaceCollection::merge(FaceCollection& rhs)
{
	this->faces.splice(this->faces.end(), rhs.faces);
	renumber();
	rhs.faces.clear();
}

Face* FaceCollection::create(Edge* v1, Edge* v2, Edge* v3)
{
	auto f = new Face(v1, v2, v3);
	faces.push_back(f);
	return f;
}

void FaceCollection::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}

void FaceCollection::cleaning()
{
	std::list<Face*> shrinked = getDegenerateds();
	for (auto f : shrinked) {
		remove(f);
	}
	renumber();
}

void FaceCollection::renumber()
{
	nextId = 0;
	for (auto f : faces) {
		f->changeId(nextId++);
	}

}

void FaceCollection::remove(Face* f)
{
	faces.remove(f);
	delete f;
}

Face* FaceCollection::findById(const int id)
{
	for (auto f : faces) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}

void FaceCollection::add(Face* f)
{
	faces.push_back(f);
}

std::list<Face*> FaceCollection::getDegenerateds()
{
	std::list<Face*> shrinked;
	for (auto f : faces) {
		if (f->isDegenerated()) {
			shrinked.push_back(f);
		}
	}
	return shrinked;
}
