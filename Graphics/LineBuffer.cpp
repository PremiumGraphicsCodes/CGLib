#include "LineBuffer.h"

#include "../Polygon/PolygonObject.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/Bone.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;

void LineBuffer::clear()
{
	position.clear();
	color.clear();
	this->ids.clear();
}


void LineBuffer::add(const Line3d<float>& line,const ColorRGBA<float>& color)
{
	position.add(line.getStart());
	position.add(line.getEnd());
	this->color.add(color);
	this->color.add(color);
	this->ids.push_back(this->ids.size());
	this->ids.push_back(this->ids.size());
}

void LineBuffer::add(const ActorObject& actor)
{
	for (auto b : actor.getBones()) {
		if (b->getOriginJoint() != nullptr && b->getDestJoint() != nullptr) {
			add(b->toLine(), ColorRGBA<float>(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}


void LineBuffer::add(const PolygonMesh& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->position.add(v->getPosition());
		this->color.add(ColorRGBA<float>(0.0, 0.0, 0.0, 1.0));
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

