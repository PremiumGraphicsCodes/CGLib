#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Face::Face(Vertex* v1, Vertex* v2, Vertex* v3) :
	v1(v1),
	v2(v2),
	v3(v3)
{
	this->normal = (v2->getPosition() - v1->getPosition()).getOuterProduct(v3->getPosition() - v1->getPosition());
	this->normal.normalize();
}

Vertex* Face::find(Vertex* v)
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


void Face::replace(Vertex* oldVertex, Vertex* newVertex)
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

Point3d<float> Face::getCenterPoint() const {
	auto pos = (v1->getPosition() + v2->getPosition() + v3->getPosition()) / 3;
	return Point3d<float>(pos);
}


std::array< Edge, 3 > Face::toEdges() const
{
	Edge e1(v1, v2, 0);
	Edge e2(v2, v3, 0);
	Edge e3(v3, v1, 0);
	return { e1, e2, e3 };

}

FaceCollection::FaceCollection()
{}

FaceCollection::FaceCollection(const std::vector<Face*>& faces) :
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

Face* FaceCollection::create(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new Face(v1, v2, v3);
	v1->addFace(f);
	v2->addFace(f);
	v3->addFace(f);
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



