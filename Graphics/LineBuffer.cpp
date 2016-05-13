#include "LineBuffer.h"

#include "../Polygon/PolygonMesh.h"
#include "../Polygon/Actor.h"
#include "../Polygon/Bone.h"

#include "DrawableID.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;

void LineBuffer::clear()
{
	position.clear();
	color.clear();
	this->ids.clear();
	this->idColors.clear();
}


void LineBuffer::add(const Line3d<float>& line,const ColorRGBA<float>& color, const int id)
{
	position.add(line.getStart());
	position.add(line.getEnd());
	this->color.add(color);
	this->color.add(color);
	this->ids.push_back(this->ids.size());
	this->ids.push_back(this->ids.size());

	DrawableID did(id);
	this->idColors.add(did.toColor());
	this->idColors.add(did.toColor());

}

void LineBuffer::add(const PolygonMesh& polygon, const ColorRGBA<float>& color)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->position.add(v->getPosition());
		this->color.add(color);
		//this->idColors.add(ColorRGBA<unsigned char>(v->getId()));
	}
	const auto faces = polygon.getFaces();
	for (auto f : faces) {
		this->ids.push_back(f->getV1()->getId());
		this->ids.push_back(f->getV2()->getId());
		this->ids.push_back(f->getV2()->getId());
		this->ids.push_back(f->getV3()->getId());
		this->ids.push_back(f->getV3()->getId());
		this->ids.push_back(f->getV1()->getId());
	}
}

