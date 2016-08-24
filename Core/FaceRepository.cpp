#include "stdafx.h"
#include "FaceRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

FaceRepository::FaceRepository() :
	nextId(0)
{}

FaceRepository::FaceRepository(const std::vector<Face*>& faces) :
	nextId(0),
	faces(faces.begin(), faces.end())
{
}


FaceRepository::FaceRepository(const std::list<Face*>& faces) :
	faces(faces),
	nextId(0)
{}

FaceRepository::~FaceRepository()
{
}

void FaceRepository::merge(FaceRepository& rhs)
{
	this->faces.splice(this->faces.end(), rhs.faces);
	renumber();
	rhs.faces.clear();
}

Face* FaceRepository::create(HalfEdge* v1, HalfEdge* v2, HalfEdge* v3)
{
	auto f = new Face(v1, v2, v3, nextId++);
	faces.push_back(f);
	return f;
}

void FaceRepository::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}

void FaceRepository::cleaning()
{
	std::list<Face*> shrinked = getDegenerateds();
	for (auto f : shrinked) {
		remove(f);
	}
	renumber();
}

void FaceRepository::renumber()
{
	nextId = 0;
	for (auto f : faces) {
		f->changeId(nextId++);
	}

}

void FaceRepository::remove(Face* f)
{
	faces.remove(f);
	delete f;
}

Face* FaceRepository::findById(const int id)
{
	for (auto f : faces) {
		if (id == f->getId()) {
			return f;
		}
	}
	return nullptr;
}

void FaceRepository::add(Face* f)
{
	faces.push_back(f);
}

std::list<Face*> FaceRepository::getDegenerateds()
{
	std::list<Face*> shrinked;
	for (auto f : faces) {
		if (f->isDegenerated()) {
			shrinked.push_back(f);
		}
	}
	return shrinked;
}
