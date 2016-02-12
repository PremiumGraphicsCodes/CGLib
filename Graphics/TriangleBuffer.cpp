#include "TriangleBuffer.h"

#include "../Polygon/Vertex.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;


namespace {
	ColorRGBA<unsigned char> toColor(const unsigned int id) {
		const auto r = 0.0f;
		const auto g = id % 255;
		const auto b = (id % 255) % 255;
		return ColorRGBA<unsigned char>(r, g, b, 255);
	}
}


void TriangleBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		add(*v, toColor( v->getId()) );
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

