#include "LineBuffer.h"

#include "../Core/PolygonMesh.h"
#include "../Core/Actor.h"
#include "../Core/Bone.h"
#include "../Core/Surface.h"
#include "../Core/Node.h"
#include "../Core/Edge.h"

#include "DrawableID.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

void LineBuffer::clear()
{
	position.clear();
	color.clear();
	this->ids.clear();
	this->idColors.clear();
}

void LineBuffer::add(const Point3d<float>& point, const ColorRGBA<float>& color)
{
	this->position.add(point.getPosition());
	this->color.add(color);
	//this->normal.add(point.getNormal());
	//this->texCoord.add(point.getParameter());
}

void LineBuffer::add(const Edge& edge, const ColorRGBA<float>& color)
{
	this->ids.push_back( edge.getStart()->getId() );
	this->ids.push_back( edge.getEnd()->getId() );
}


void LineBuffer::add(const Surface& surface, const ColorRGBA<float>& color)
{
	const auto& nodes = surface.getNodes();
	for (auto n : nodes) {
		add(*n, color);
	}
	const auto& edges = surface.getEdges();
	for (auto e : edges) {
		add(*e, color);
	}
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

