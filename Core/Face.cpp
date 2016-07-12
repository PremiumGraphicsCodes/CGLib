#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Face::Face(Vertex* v1, Vertex* v2, Vertex* v3) :
	vertices({ v1, v2, v3 })
{
	v1->addFace(this);
	v2->addFace(this);
	v3->addFace(this);
}

Vertex* Face::find(Vertex* v)
{
	auto f = std::find(vertices.begin(), vertices.end(), v);
	if (f != vertices.end()) {
		return v;
	}
	assert(false);
	return nullptr;
}

Vector3d<float> Face::getNormal() const
{
	auto normal = (vertices[1]->getPosition() - vertices[0]->getPosition()).getOuterProduct(vertices[2]->getPosition() - vertices[0]->getPosition());
	normal.normalize();
	return normal;
}


void Face::replace(Vertex* oldVertex, Vertex* newVertex)
{
	if (oldVertex == vertices[0]) {
		vertices[0] = newVertex;
	}
	else if (oldVertex == vertices[1]) {
		vertices[1] = newVertex;
	}
	else if (oldVertex == vertices[2]) {
		vertices[2] = newVertex;
	}
	else {
		assert(false);
	}
}

Point3d<float> Face::getCenterPoint() const {
	auto pos = (vertices[0]->getPosition() + vertices[1]->getPosition() + vertices[2]->getPosition()) / 3;
	return Point3d<float>(pos);
}


std::array< Edge, 3 > Face::toEdges() const
{
	Edge e1(vertices[0], vertices[1], 0);
	Edge e2(vertices[1], vertices[2], 0);
	Edge e3(vertices[2], vertices[0], 0);
	return { e1, e2, e3 };

}

bool Face::has(Vertex* v) const
{
	auto f = std::find(vertices.begin(), vertices.end(), v);
	return (f != vertices.end());
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



