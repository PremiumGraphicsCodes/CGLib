#include "stdafx.h"
#include "TriangleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Core;

TriangleBuffer::TriangleBuffer()
{
}

TriangleBuffer::TriangleBuffer(const PolygonRepository& factory)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		this->positions.add(v->getPosition());
		this->normals.add(v->getNormal());
		this->texCoords.add(v->getParameter());
	}
}

void TriangleBuffer::add(const PolygonMesh& polygon, Material* mat)
{
	const auto& faces = polygon.getFaces();
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		indices.push_back(f->getV1()->getId());
		indices.push_back(f->getV2()->getId());
		indices.push_back(f->getV3()->getId());
	}
	TriangleBufferBlock block(indices, mat);
	blocks.push_back(block);
}

void TriangleBuffer::add(const ColoredPolygon& polygon)
{
	add(*polygon.getPolygon(), polygon.getMaterial());
}