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

PolygonMesh::PolygonMesh(const std::list<Vertex*>& vertices, const std::list<Face*>& faces, const unsigned int id) :
	vertices(vertices),
	faces(faces),
	id(id)
{}

#include "../Math/Curve3d.h"

void PolygonMesh::clear()
{
	//positions.clear();
	//normals.clear();
	//texCoords.clear();
	vertices.clear();
	faces.clear();
}

#include "../Math/Matrix4d.h"

void PolygonMesh::transform(const Matrix4d<float>& matrix)
{
	for (auto v : vertices) {
		v->transform(matrix);
	}
}

std::vector<int> PolygonMesh::toIndices() const
{
	std::vector<int> results;
	for (auto v : vertices) {
		results.push_back( v->getId() );
	}
	return results;
}

//void create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

#include "Edge.h"

void PolygonMesh::smooth(Vertex* center)
{
	auto& fs = center->getFaces();
	std::list<Vertex*> neighbors = center->getNeighbors();
	Vector3d<float> position = center->getPosition();
	for (auto& n : neighbors) {
		position += (n->getPosition() - center->getPosition()) / neighbors.size();
	}
	center->moveTo(position);
}

void PolygonMesh::simplify(const Edge& e)
{
	auto center = e.getMidPoint();
	e.getStart()->moveTo(center.getPosition());
	e.getEnd()->moveTo(center.getPosition());
}

void PolygonMesh::removeOverlappedVertices()
{
	VertexCollection vc(vertices);
	vc.sort();
	this->vertices = vc.get();
}


void PolygonMesh::cleaning()
{
	VertexCollection vc(vertices);
	vc.renumber();
	this->vertices = vc.get();
	//faces.cleaning();
}

void PolygonMesh::add(Face* f)
{
	faces.push_back(f);
}

void PolygonMesh::add(Vertex* v)
{
	vertices.push_back(v);
}

bool PolygonMesh::has(Face* f)
{
	for (auto f1 : faces) {
		if (f1 == f) {
			return true;
		}
	}
	return false;
}

void PolygonMesh::remove(Face* f)
{
	faces.remove(f);
}

PolygonMesh* PolygonMesh::clone(const int id)
{
	return new PolygonMesh(vertices, faces, id);
}
