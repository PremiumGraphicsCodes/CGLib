#include "stdafx.h"
#include "TriangleIdBuffer.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TriangleIdBuffer::TriangleIdBuffer() :
	nextIndex(0)
{
}


void TriangleIdBuffer::add(const Surface& surface)
{
	auto si = surface.toIndices();
	this->indices.insert( indices.end(), si.begin(), si.end());
	const auto& nodes = surface.getNodes();
	for (auto& n : nodes) {
		add(*n, surface.getId());
	}
}

#include "DrawableID.h"

void TriangleIdBuffer::add(const Point3d<float>& point, const int id)
{
	this->positions.add(point.getPosition());
	DrawableID did(id);
	this->idColors.add(did.toColor().toArray4());
}
