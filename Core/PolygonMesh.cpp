#include "stdafx.h"
#include "PolygonMesh.h"

#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;


PolygonMesh::~PolygonMesh()
{
	clear();
}

PolygonMesh::PolygonMesh(const std::list<Face*>& faces, const unsigned int id) :
	faces(faces),
	id(id)
{}

void PolygonMesh::clear()
{
	faces.clear();
}

//void create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

#include "HalfEdge.h"

void PolygonMesh::smooth(const float angle)
{
	auto edges = findInnerVertices();
	for (auto e : edges) {
		smooth(e);
	}
}


void PolygonMesh::smooth(Vertex* center)
{
	std::list<Vertex*> neighbors;
	auto fs = getFaces();
	for (auto f : fs) {
		for (auto e : f->getEdges()) {
			if (e->getStart() == center) {
				neighbors.push_back(e->getEnd());
			}
		}
	}
	neighbors.sort();
	neighbors.unique();
	//std::list<Vertex*> neighbors = center->getNeighbors();
	Vector3d<float> diff(0,0,0);
	for (auto& n : neighbors) {
		diff += (n->getPosition() - center->getPosition()) / neighbors.size();
	}
	const auto& normal = center->getNormal();
	const auto length = normal.getInnerProduct(-diff);
	diff += length * normal;
	//diff *= normal.getInnerProduct(diff);
	
	center->move(diff);
}

HalfEdge* PolygonMesh::getShortestEdge()
{
	std::list<HalfEdge> edges;
	auto minEdge = faces.front()->getEdges().front();
	for (auto f : faces) {
		auto edges = f->getEdges();
		for (auto e : edges) {
			if (e->getLength() < minEdge->getLength()) {
				minEdge = e;
			}
		}
	}
	return minEdge;
}


void PolygonMesh::simplify(const HalfEdge& e)
{
	auto center = e.getMidPoint();
	e.getStart()->moveTo(center.getPosition());
	e.getEnd()->moveTo(center.getPosition());
}


void PolygonMesh::add(Face* f)
{
	faces.push_back(f);
}

bool PolygonMesh::has(Face* f)
{
	return std::find(faces.begin(), faces.end(), f) != faces.end();
}

bool PolygonMesh::has(HalfEdge* e)
{
	const auto& edges = getEdges();
	return std::find(edges.begin(), edges.end(), e) != edges.end();
}

bool PolygonMesh::has(Vertex* v)
{
	const auto& vertices = getVertices();
	return std::find(vertices.begin(), vertices.end(), v) != vertices.end();
}

std::list<Vertex*> PolygonMesh::getVertices() const
{
	std::list<Vertex*> vertices;
	for (auto f : faces) {
		auto vs = f->getVertices();
		vertices.insert(vertices.end(), vs.begin(), vs.end());
	}
	vertices.sort();
	vertices.unique();
	return vertices;
}

std::list<HalfEdge*> PolygonMesh::getEdges() const
{
	std::list<HalfEdge*> edges;
	for (auto f : faces) {
		auto es = f->getEdges();
		edges.insert(edges.end(), es.begin(), es.end());
	}
	edges.sort();
	edges.unique();
	return edges;
}

void PolygonMesh::remove(Face* f)
{
	faces.remove(f);
}

PolygonMesh* PolygonMesh::clone(const int id)
{
	return new PolygonMesh(faces, id);
}

void PolygonMesh::mergeDouble(PolygonMesh* rhs, float distance)
{
	auto faces1 = this->getFaces();
	auto faces2 = rhs->getFaces();
	for (auto f1 : faces1) {
		for (auto f2 : faces2) {
			f1->mergeDouble(*f2, distance);
		}
	}
}

Vector3d<float> PolygonMesh::getCenter() const
{
	Vector3d<float> center;
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		center += v->getPosition() / vs.size();
	}
	return center;
}

void PolygonMesh::move(const Vector3d<float>& v)
{
	const auto& vs = getVertices();
	for (auto& vert : vs) {
		vert->move(v);
	}
}

void PolygonMesh::scale(const Vector3d<float>& s)
{
	const auto& center = getCenter();
	move(-center);
	const auto& vs = getVertices();
	for (auto& vert : vs) {
		vert->scale(s);
	}
	move(center);
}

void PolygonMesh::rotate(const Quaternion<float>& quaternion)
{
	const auto& center = getCenter();
	move(-center);
	const auto& vs = getVertices();
	const auto& matrix = quaternion.toMatrix();
	for (auto& vert : vs) {
		vert->transform(matrix);
	}
	move(center);

}

void PolygonMesh::merge(PolygonMesh& rhs)
{
	faces.splice(faces.end(), rhs.faces);
	rhs.clear();
}

void PolygonMesh::reverse()
{
	auto vs = getVertices();
	for (auto v : vs) {
		v->reverse();
	}
	for (auto f: faces) {
		f->reverse();
	}
}

std::list<Vertex*> PolygonMesh::findBoundaryVertices()
{
	const auto& bEdges = findBoundaryEdges();
	std::list<Vertex*> results;
	for (const auto& b : bEdges) {
		results.push_back( b->getStart() );
	}
	results.sort();
	results.unique();
	return results;
}

std::list<Vertex*> PolygonMesh::findInnerVertices()
{
	auto all = getVertices();
	auto boundaries = findBoundaryVertices();
	std::list<Vertex*> inners;
	std::set_difference(
		all.begin(), all.end(),
		boundaries.begin(), boundaries.end(),
		std::back_inserter(inners)
	);
	return inners;
}


std::list<HalfEdge*> PolygonMesh::findBoundaryEdges()
{
	std::list<HalfEdge*> results;
	const auto& edges = getEdges();
	for (auto e : edges) {
		if (e->isBoundary()) {
			results.push_back(e);
		}
	}
	return results;
}

void PolygonMesh::updateNormals()
{
	for (auto f : faces) {
		for (auto v : f->getVertices()) {
			v->setNormal(Vector3d<float>(0, 0, 0));
		}
	}
	for (auto f : faces) {
		const auto area = f->getArea() * 1.0e+6f;
		//assert(area > 0);
		const auto& normal = f->getNormal();
		for (auto v : f->getVertices()) {
			v->setNormal(v->getNormal() + area * normal);
		}
	}
	for (auto f : faces) {
		for (auto v : f->getVertices()) {
			auto n = v->getNormal();
			v->setNormal(n.normalized());
		}
	}
}
