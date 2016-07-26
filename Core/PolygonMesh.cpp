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

#include "Edge.h"

void PolygonMesh::smooth(Vertex* center)
{
	/*
	std::list<Vertex*> neighbors = center->getNeighbors();
	Vector3d<float> position = center->getPosition();
	for (auto& n : neighbors) {
		position += (n->getPosition() - center->getPosition()) / neighbors.size();
	}
	center->moveTo(position);
	*/
}

Edge* PolygonMesh::getShortestEdge()
{
	std::list<Edge> edges;
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


void PolygonMesh::simplify(const Edge& e)
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

bool PolygonMesh::has(Edge* e)
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

std::list<Edge*> PolygonMesh::getEdges() const
{
	std::list<Edge*> edges;
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
