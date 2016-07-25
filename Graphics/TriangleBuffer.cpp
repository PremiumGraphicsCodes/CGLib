#include "stdafx.h"
#include "TriangleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Core;

TriangleBuffer::TriangleBuffer()
{
}

TriangleBuffer::TriangleBuffer(const PolygonFactory& factory)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		this->positions.add(v->getPosition());
		this->normals.add(v->getNormal());
		this->texCoords.add(v->getParameter());
		this->colors.add(ColorRGBA<float>(1.0f, 0.0f, 0.0f, 1.0f));
	}
}


void TriangleBuffer::add(const Point3d<float>& point)
{
	this->positions.add( point.getPosition() );
	this->normals.add(point.getNormal());
	this->texCoords.add(point.getParameter());
}


void TriangleBuffer::add(const PolygonMesh& polygon)
{
	const auto& faces = polygon.getFaces();
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

void TriangleBuffer::clear()
{
	indices.clear();
	positions.clear();
	normals.clear();
	colors.clear();
}

std::vector<unsigned int> TriangleBuffer::getIndices(const unsigned int startIndex, const unsigned int endIndex) const
{
	std::vector<unsigned int> results;
	for (unsigned int i = startIndex; i < endIndex; ++i) {
		results.push_back(indices[i]);
	}
	return results;
}