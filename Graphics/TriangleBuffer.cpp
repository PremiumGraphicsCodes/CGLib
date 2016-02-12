#include "TriangleBuffer.h"

#include "../Polygon/Vertex.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;


void TriangleBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		add(*v, ColorRGBA<unsigned char>( v->getId()) );
	}
	const auto faces = polygon.getFaces();
	for (auto f : faces) {
		this->indices.push_back(f->getV1()->getId());
		this->indices.push_back(f->getV2()->getId());
		this->indices.push_back(f->getV3()->getId());
	}
}

void TriangleBuffer::add(const Vertex& vertex, const ColorRGBA<unsigned char>& color)
{
	this->positions.add(vertex.getPosition());
	this->normals.add(vertex.getNormal());
	this->colors.add(color);

}

