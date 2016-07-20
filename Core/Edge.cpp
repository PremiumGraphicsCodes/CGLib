#include "stdafx.h"
#include "Edge.h"
#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Edge::Edge(Vertex* start, Vertex* end, const int id) :
	start(start),
	end(end),
	id(id),
	face(nullptr)
{
	if (start) {
		start->addOut(this);
	}
	if (end) {
		end->addIn(this);
	}
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

bool Edge::isSame(const Edge& rhs) const
{
	return
		this->start == rhs.start &&
		this->end == rhs.end;
}


bool Edge::isShared(const Edge& rhs) const
{
	if (isSame(rhs)) {
		return true;
	}
	if (isReverse(rhs)) {
		return true;
	}
	return false;
}

bool Edge::isCollapsed() const
{
	return
		start == nullptr ||
		end == nullptr;
}

bool Edge::isIsolated() const
{
	return face == nullptr;
}

#include "Face.h"

float Edge::calculateCollapseCost() const
{
	/*
	const auto length = getLength();
	float curvature = 0;

	std::list<Face*> sides;
	for (auto f : start->getFaces()) {
		if (f->has(end)) {
			sides.push_back(f);
		}
	}

	for (auto f1 : start->getFaces()) {
		float minCurve = 1;
		for (auto f2 : sides) {
			float innerProduct = f1->getNormal().getInnerProduct(f2->getNormal());
			minCurve = std::min(minCurve, (1 - innerProduct) / 2.0f);
		}
		curvature = std::max(curvature, minCurve);
	}
	return length * curvature;
	*/
	return 0.0f;
}

bool Edge::isDegenerated() const
{
	return getLength() < Tolerance<float>::getLooseTolerance();
}
