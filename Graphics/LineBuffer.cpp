#include "stdafx.h"
#include "LineBuffer.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

LineBuffer::LineBuffer(const PolygonFactory& factory)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		this->position.add(v->getPosition());
		this->color.add(ColorRGBA<float>(1, 0, 0, 1));
	}
}


LineBuffer::LineBuffer(const Polyline3d<float>& polyline, const ColorRGBA<float>& color)
{
	add(polyline, color);
}

void LineBuffer::clear()
{
	position.clear();
	color.clear();
	this->ids.clear();
}

void LineBuffer::add(const Point3d<float>& point, const ColorRGBA<float>& color)
{
	this->position.add(point.getPosition());
	this->color.add(color);
}

void LineBuffer::add(const Edge& edge, const ColorRGBA<float>& color)
{
	this->ids.push_back( edge.getStart()->getId() );
	this->ids.push_back( edge.getEnd()->getId() );
}

void LineBuffer::add(const Polyline3d<float>& polyline, const ColorRGBA<float>& color)
{
	const auto& lines = polyline.toLines();
	for (int i = 0; i < lines.size(); ++i) {
		add(lines[i], color);
	}

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

void LineBuffer::add(const PolygonMesh& polygon)
{
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
