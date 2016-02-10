#include "TriangleBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;

void TriangleBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->positions.add( v->getPosition() );
		this->normals.add(v->getNormal());
	}
	const auto faces = polygon.getFaces();
	for (auto f : faces) {
		this->indices.push_back(f->getV1()->getId());
		this->indices.push_back(f->getV2()->getId());
		this->indices.push_back(f->getV3()->getId());
	}
}
