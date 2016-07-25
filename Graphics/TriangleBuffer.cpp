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
	}
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