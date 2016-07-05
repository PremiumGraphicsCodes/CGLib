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

void TriangleIdBuffer::add(const Surface& surface, const DrawableID& did)
{
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
}

void TriangleIdBuffer::add(const Surface& surface, const unsigned char groupId)
{
	const auto& nodes = surface.getNodes();
	for (auto& n : nodes) {
		positions.add(n->getPosition());
	}

	for (const auto& f : surface.getFaces()) {
		TriangleIdBlock block(f->getNodeIds(), DrawableID(f->getId(), groupId));
		blocks.push_back(block);
	}
	nextIndex += surface.getNodes().size();
}

