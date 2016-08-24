#include "stdafx.h"
#include "TriangleIdBuffer.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TriangleIdBuffer::TriangleIdBuffer()
{
}

TriangleIdBuffer::TriangleIdBuffer(const PolygonRepository& factory)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		this->positions.add(v->getPosition());
	}
}


void TriangleIdBuffer::clear()
{
	blocks.clear();
	positions.clear();
}

void TriangleIdBuffer::add(const PolygonMesh& surface, const unsigned char groupId)
{
	for (const auto& f : surface.getFaces()) {
		std::vector<unsigned int> ids(3);
		ids[0] = f->getV1()->getId();
		ids[1] = f->getV2()->getId();
		ids[2] = f->getV3()->getId();
		TriangleIdBlock block(ids, DrawableID(f->getId(), groupId));
		blocks.push_back(block);
	}
}


