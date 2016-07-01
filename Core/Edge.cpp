#include "stdafx.h"
#include "Edge.h"
#include "Node.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Edge::Edge(Node* start, Node* end, const int id) :
	start(start),
	end(end),
	id(id)
{
}


Vector3d<float> Edge::getVector() const
{
	return end->getPosition() - start->getPosition();
}

float Edge::getLength() const
{
	return getVector().getLength();
}

Line3d<float> Edge::toLine() const
{
	return Line3d<float>(start->getPosition(), end->getPosition());
}

Point3d<float> Edge::getMidPoint() const
{
	return start->lerp(*end, 0.5f);
}

Edge* Edge::createReverse(const int id) const
{
	return new Edge(end, start, id);
}

bool Edge::isReverse(const Edge& rhs) const
{
	return
		this->start == rhs.end &&
		this->end == rhs.start;
}

void Edge::move(const Vector3d<float>& v)
{
	this->start->move(v);
	this->end->move(v);
}
