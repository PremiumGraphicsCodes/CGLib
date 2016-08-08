#include "stdafx.h"
#include "HalfEdge.h"
#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

HalfEdge::HalfEdge(Vertex* start, Vertex* end, const int id) :
	start(start),
	end(end),
	id(id),
	next(nullptr),
	face(nullptr),
	pair(nullptr)
{
}


Vector3d<float> HalfEdge::getVector() const
{
	return end->getPosition() - start->getPosition();
}

float HalfEdge::getLength() const
{
	return getVector().getLength();
}

Line3d<float> HalfEdge::toLine() const
{
	return Line3d<float>(start->getPosition(), end->getPosition());
}

Point3d<float> HalfEdge::getMidPoint() const
{
	return start->lerp(*end, 0.5f);
}

HalfEdge* HalfEdge::createReverse(const int id) const
{
	return new HalfEdge(end, start, id);
}

bool HalfEdge::isReverse(const HalfEdge& rhs) const
{
	return
		this->start == rhs.end &&
		this->end == rhs.start;
}

void HalfEdge::move(const Vector3d<float>& v)
{
	this->start->move(v);
	this->end->move(v);
}

void HalfEdge::connect(HalfEdge* next)
{
	next->prev = this;
	this->next = next;
}

bool HalfEdge::isSame(const HalfEdge& rhs) const
{
	return
		this->start == rhs.start &&
		this->end == rhs.end;
}


bool HalfEdge::isShared(const HalfEdge& rhs) const
{
	if (isSame(rhs)) {
		return true;
	}
	if (isReverse(rhs)) {
		return true;
	}
	return false;
}

bool HalfEdge::isCollapsed() const
{
	return
		start == nullptr ||
		end == nullptr;
}

bool HalfEdge::isIsolated() const
{
	return face == nullptr;
}

#include "Face.h"

float HalfEdge::calculateCollapseCost() const
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

bool HalfEdge::isDegenerated() const
{
	return getLength() < Tolerance<float>::getLooseTolerance();
}

bool HalfEdge::isDegenerated(const float length) const
{
	return getLength() < length;
}

void HalfEdge::toDenerate()
{
	end = start;
}

void HalfEdge::reverse()
{
	std::swap( start, end );
	std::swap( prev, next );
}

HalfEdge* HalfEdge::split(Vertex* v)
{
	auto next = clone(-1);
	this->changeEnd(v);
	next->changeStart(v);
	this->connect(next);
	return next;
}

HalfEdge* HalfEdge::clone(const int id) const
{
	HalfEdge* e = new HalfEdge(start, end, id);
	e->start = start;
	e->end = end;
	e->face = face;
	e->prev = prev;
	e->next = next;
	e->pair = pair;
	return e;
}

bool HalfEdge::has(Vertex* e)
{
	return (start == e) || (end == e);
}

Line3d<float> HalfEdge::getCurve() const
{
	return toLine();
}

