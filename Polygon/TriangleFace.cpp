#include "TriangleFace.h"
#include "Vertex.h"

using namespace Crystal::Polygon;

TriangleFace::TriangleFace(Vertex* v1, Vertex* v2, Vertex* v3) :
	v1(v1),
	v2(v2),
	v3(v3)
{
	this->normal = (v2->getPosition()->getVector() - v1->getPosition()->getVector()).getOuterProduct(v3->getPosition()->getVector() - v1->position->getVector());
	this->normal.normalize();
}

Vertex* TriangleFace::find(Vertex* v)
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


void TriangleFace::replace(Vertex* oldVertex, Vertex* newVertex) {
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
