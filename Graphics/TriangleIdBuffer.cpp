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
	indices.clear();
	positions.clear();
	idColors.clear();
	nextIndex = 0;
}

void TriangleIdBuffer::add(const Surface& surface, const DrawableID& did)
{
	auto si = surface.toIndices();
	this->indices.insert( indices.end(), si.begin(), si.end());
	const auto& nodes = surface.getNodes();
	for (auto& n : nodes) {
		add(*n, did);
	}
}


void TriangleIdBuffer::add(const Point3d<float>& point, const DrawableID& did)
{
	this->positions.add(point.getPosition());
	this->idColors.add(did.toColor().toArray4());
}
