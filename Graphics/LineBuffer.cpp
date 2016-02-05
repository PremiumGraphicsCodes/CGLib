#include "LineBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;

void LineBuffer::clear()
{
	position.clear();
	color.clear();
}


void LineBuffer::add(const Line3d<float>& line,const ColorRGBA<float>& color)
{
	position.add(line.getStart());
	position.add(line.getEnd());
	this->color.add(color);
	this->color.add(color);
}

void LineBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->position.add(v->getPosition()->getVector());
		this->color.add(ColorRGBA<float>(1.0, 1.0, 0.0, 1.0));
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

