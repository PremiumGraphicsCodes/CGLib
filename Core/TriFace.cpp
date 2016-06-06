#include "TriFace.h"
#include "Vertex.h"

using namespace Crystal::Core;

TriFace::TriFace(Vertex* v1, Vertex* v2, Vertex* v3) :
	v1(v1),
	v2(v2),
	v3(v3)
{
	this->normal = (v2->getPosition() - v1->getPosition()).getOuterProduct(v3->getPosition() - v1->getPosition());
	this->normal.normalize();
}

Vertex* TriFace::find(Vertex* v)
{
	if (v == v1) {
		return v1;
	}
	if (v == v2) {
		return v2;
	}
	if (v == v3) {
		return v3;
	}
	assert(false);
	return nullptr;
}


void TriFace::replace(Vertex* oldVertex, Vertex* newVertex)
{
	if (oldVertex == v1) {
		v1 = newVertex;
	}
	else if (oldVertex == v2) {
		v2 = newVertex;
	}
	else if (oldVertex == v3) {
		v3 = newVertex;
	}
	else {
		assert(false);
	}
}

FaceCollection::FaceCollection()
{}

FaceCollection::FaceCollection(const std::vector<TriFace*>& faces) :
	faces(faces)
{}

FaceCollection::~FaceCollection()
{
}

void FaceCollection::merge(FaceCollection& rhs)
{
	this->faces.insert(this->faces.end(), rhs.faces.begin(), rhs.faces.end());
	rhs.faces.clear();
}

TriFace* FaceCollection::create(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new TriFace(v1, v2, v3);
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
