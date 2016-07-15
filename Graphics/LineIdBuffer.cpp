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

void LineIdBuffer::add(const PolygonMesh& mesh, const unsigned char groupId)
{
	const auto& faces = mesh.getFaces();
	for (auto f : faces) {
		const auto edges = f->toEdges();
		for (auto e : edges) {
			add(e.toLine(), DrawableID(e.getId(), groupId));
		}
	}
}


void LineIdBuffer::add(const PolygonMesh& mesh, const DrawableID& did)
{
	const auto& faces = mesh.getFaces();
	for (auto f : faces) {
		const auto edges = f->toEdges();
		for (auto e : edges) {
			add(e.toLine(), did);
		}
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

void LineIdBuffer::add(const PolygonFactory& factory, const DrawableID& did)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		this->position.add(v->getPosition());
		this->idColors.add(did.toColor());
	}
	const auto& faces = factory.getFaces();
	for (const auto& f : faces) {
		this->ids.push_back(f->getV1()->getId());
		this->ids.push_back(f->getV2()->getId());
		this->ids.push_back(f->getV2()->getId());
		this->ids.push_back(f->getV3()->getId());
		this->ids.push_back(f->getV3()->getId());
		this->ids.push_back(f->getV1()->getId());
	}
}
