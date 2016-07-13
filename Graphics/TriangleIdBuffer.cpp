#include "stdafx.h"
#include "TriangleIdBuffer.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TriangleIdBuffer::TriangleIdBuffer() :
	nextIndex(0)
{
}

void TriangleIdBuffer::clear()
{
	blocks.clear();
	positions.clear();
	nextIndex = 0;
}

void TriangleIdBuffer::add(const PolygonMesh& surface, const DrawableID& did)
{
	/*
	auto si = surface.toIndices();
	for (auto& s : si) {
		s += nextIndex;
	}
	TriangleIdBlock block(si, did);
	blocks.push_back(block);
	const auto& nodes = surface.getNodes();
	for (auto& n : nodes) {
		positions.add(n->getPosition());
	}
	nextIndex += surface.getNodes().size();
	*/
}

void TriangleIdBuffer::add(const PolygonMesh& surface, const unsigned char groupId)
{
	const auto& nodes = surface.getVertices();
	for (auto& n : nodes) {
		positions.add(n->getPosition());
	}

	for (const auto& f : surface.getFaces()) {
		std::vector<unsigned int> ids(3);
		ids[0] = f->getV1()->getId();
		ids[1] = f->getV2()->getId();
		ids[2] = f->getV3()->getId();
		TriangleIdBlock block(ids, DrawableID(f->getId(), groupId));
		blocks.push_back(block);
	}
	nextIndex += surface.getVertices().size();
}

