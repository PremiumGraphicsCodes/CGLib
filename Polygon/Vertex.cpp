#include "Vertex.h"
#include "TriangleFace.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

void Vertex::setFace(TriangleFace* f) {
	this->f = f;
	this->normal = f->getNormal();
}


