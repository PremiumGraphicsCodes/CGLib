#include "stdafx.h"
#include "LineIdBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

void LineIdBuffer::clear()
{
	position.clear();
	idColors.clear();
	ids.clear();
}

void LineIdBuffer::add(const Surface& surface)
{
	const auto& edges = surface.getEdges();
	for (auto e : edges) {
		add(e->toLine(), DrawableID(e->getId(), surface.getId()));
	}
}


void LineIdBuffer::add(const Surface& surface, const DrawableID& did)
{
	const auto& edges = surface.getEdges();
	for (auto e : edges) {
		add(e->toLine(), did);
	}

}

void LineIdBuffer::add(const Line3d<float>& line, const DrawableID& did)
{
	this->position.add(line.getStart());
	this->position.add(line.getEnd());


	this->idColors.add(did.toColor());
	this->idColors.add(did.toColor());

	this->ids.push_back(ids.size());
	this->ids.push_back(ids.size());
}

void LineIdBuffer::add(const Polyline3d<float>& polyline, const DrawableID& did)
{
	const auto& lines = polyline.toLines();
	for (const auto& l : lines) {
		add(l, did);
	}
}
