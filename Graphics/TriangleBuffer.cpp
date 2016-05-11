#include "TriangleBuffer.h"

#include "../Polygon/Vertex.h"

#include "DrawableID.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;


void TriangleBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->positions.add(v->getPosition());
		this->normals.add(v->getNormal());
		this->texCoords.add(v->getTexCoord());
		this->colors.add(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));
		
		DrawableID id(polygon.getId());
		this->idColors.add(id.toColor());
	}
	const auto faces = polygon.getFaces();
	for (auto f : faces) {
		this->indices.push_back(f->getV1()->getId());
		this->indices.push_back(f->getV2()->getId());
		this->indices.push_back(f->getV3()->getId());
	}
}

void TriangleBuffer::add(const Vertex& vertex, const ColorRGBA<float>& color)
{
	this->positions.add(vertex.getPosition());
	this->normals.add(vertex.getNormal());
	this->colors.add(color);
	//this->idColors.add()
}

void TriangleBuffer::add(const Triangle<float>& triangle)
{
	positions.add(triangle.getv0());
	positions.add(triangle.getv1());
	positions.add(triangle.getv2());
	normals.add(triangle.getNormal());
	normals.add(triangle.getNormal());
	normals.add(triangle.getNormal());
	indices.push_back(nextIndex++);
	indices.push_back(nextIndex++);
	indices.push_back(nextIndex++);
}

void TriangleBuffer::clear()
{
	nextIndex = 0;
	indices.clear();
	positions.clear();
	normals.clear();
	colors.clear();
	idColors.clear();
}

std::vector<unsigned int> TriangleBuffer::getIndices(const unsigned int startIndex, const unsigned int endIndex) const
{
	std::vector<unsigned int> results;
	for (unsigned int i = startIndex; i < endIndex; ++i) {
		results.push_back(indices[i]);
	}
	return results;
}