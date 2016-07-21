#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Face::Face(Edge* e1, Edge* e2, Edge* e3, const int id) :
	id(id)
{
	edges[0] = e1;
	edges[1] = e2;
	edges[2] = e3;
}


Face::Face(const std::array<Edge*, 3>& edges, const int id) :
	edges( edges ),
	id(id)
{
	edges[0]->setFace(this);
	edges[1]->setFace(this);
	edges[2]->setFace(this);
}

Vertex* Face::find(Vertex* v)
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	if (f != vertices.end()) {
		return v;
	}
	assert(false);
	return nullptr;
}

Vector3d<float> Face::getNormal() const
{
	auto vertices = getVertices();
	auto normal = (vertices[1]->getPosition() - vertices[0]->getPosition()).getOuterProduct(vertices[2]->getPosition() - vertices[0]->getPosition());
	normal.normalize();
	return normal;
}


Point3d<float> Face::getCenterPoint() const {
	auto vertices = getVertices();
	auto pos = (vertices[0]->getPosition() + vertices[1]->getPosition() + vertices[2]->getPosition()) / 3;
	return Point3d<float>(pos);
}

std::array< Edge*, 3 > Face::getEdges() const
{
	return edges;
}

std::array< Vertex*, 3 > Face::getVertices() const
{
	return{ edges[0]->getStart(), edges[1]->getStart(), edges[2]->getStart() };
}

bool Face::has(Vertex* v) const
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	return (f != vertices.end());
}

float Face::getArea() const
{
	auto vertices = getVertices();
	auto v1 = (vertices[1]->getPosition() - vertices[0]->getPosition());
	auto v2 = (vertices[2]->getPosition() - vertices[1]->getPosition());
	return v1.getOuterProduct(v2).getLength() / 2.0f;
}

Orientation Face::getOrientation(const Vector3d<float>& pos) const
{
	auto inner = pos.getInnerProduct(getNormal());
	if (inner > Tolerance<float>::getLooseTolerance()) {
		return Orientation::CCW;
	}
	else if (inner < -Tolerance<float>::getLooseTolerance()) {
		return Orientation::CW;
	}
	else {
		return Orientation::None;
	}
}

bool Face::isDegenerated() const
{
	return getArea() < Tolerance<float>::getLooseTolerance();
}

void Face::toDegenerate()
{
	edges[0]->toDenerate();
	edges[1]->changeStart(edges[0]->getEnd());
	edges[1]->toDenerate();
	edges[2]->changeStart(edges[0]->getEnd());
	edges[2]->toDenerate();
	//edges[1]->toDenerate();
	//edges[2]->toDenerate();
}
