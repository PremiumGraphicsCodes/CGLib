#include "stdafx.h"
#include "PolygonMesh.h"

#include "Vertex.h"
#include "TriFace.h"

#include "../Math/Sphere.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;



PolygonMesh::~PolygonMesh()
{
	clear();
}


Vertex* PolygonMesh::createVertex(Vector3d<float> position, Vector3d<float> normal, Vector2d<float> texCoord)
{
	return vertices.create(position, normal, texCoord);
}

Vertex* PolygonMesh::createVertex(Point3d<float> point)
{
	return vertices.create(point.getPosition(), point.getNormal(), point.getParameter());
}


Vertex* PolygonMesh::findVertexById(const unsigned int id) const
{
	for (auto v : vertices) {
		if (v->getId() == id) {
			return v;
		}
	}
	return nullptr;
}

/*
Face* PolygonObject::findFaceById(const unsigned int id) const
{
	for (auto f : faces) {
		if (f->getId() == id) {
			return f;
		}
	}
	return nullptr;
}
*/



TriFace* PolygonMesh::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	return faces.create(v1, v2, v3);
}

TriFace* PolygonMesh::createFace(const int vindex1, const int vindex2, const int vindex3)
{
	auto v1 = vertices[vindex1];
	auto v2 = vertices[vindex2];
	auto v3 = vertices[vindex3];
	return createFace(v1, v2, v3);
}

std::list< TriFace* > PolygonMesh::createFaces(const std::vector<int>& ids)
{
	std::list< TriFace* > fs;
	const auto origin = ids[0];
	for (size_t i = 1; i < ids.size()-1; i++) {
		auto id1 = ids[i];
		auto id2 = ids[i + 1];
		fs.push_back( createFace(vertices[origin], vertices[id1], vertices[id2]) );
	}
	return fs;
}


std::list< TriFace* > PolygonMesh::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< TriFace* > fs;
	auto origin = vertices[0];
	for (size_t i = 1; i < vertices.size() - 1; i++) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		fs.push_back(createFace(origin, v1, v2));
		v1->addFace( fs.back() );
		v2->addFace( fs.back() );
	}
	return fs;
}
#include "../Math/Curve3d.h"

void PolygonMesh::merge(PolygonMesh* rhs)
{
	this->vertices.merge(rhs->vertices);
	this->faces.merge(rhs->faces);
}

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

PolygonMesh* PolygonMesh::clone(const unsigned int id)
{
	PolygonMesh* newPolygon = new PolygonMesh(id);
	for (auto v : vertices) {
		newPolygon->createVertex( v->getPosition(), v->getNormal(), v->getParameter());
	}
	for (auto f : faces) {
		newPolygon->createFace(f->getV1()->getId(), f->getV2()->getId(), f->getV3()->getId());
	}
	return newPolygon;
}

#include "NodeGrid.h"

void PolygonMesh::create(const Curve3d<float>& curve, const int id)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = createVertex(pos, normal);
			grid.set(u, v, n);
		}
	}

	const auto& cells = grid.toQuadCells();
	std::vector<TriangleCell> triangleCells;
	for (const auto& c : cells) {
		const auto& tCells = c.toTriangleCells();	
		triangleCells.insert(triangleCells.end(), tCells.begin(), tCells.end());
	}

	for (const auto& t : triangleCells) {
		auto n0 = t.get()[0];
		auto n1 = t.get()[1];
		auto n2 = t.get()[2];
		createFace(n0, n1, n2);
		//TriFace face(n0, n1, n2);
	}
//	return create(id, createNodes, createEdges, createFaces);

}

#include "../Math/CircularCurve3d.h"

void PolygonMesh::create(const CircularCurve3d<float>& curve, const int id)
{
	Vertex* centerNode = createVertex(curve.getCenter().getPosition());

	std::vector<Vertex*> createdNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		Vertex* node = createVertex(curve.get(i));
		createdNodes.push_back(node);
	}
	for (int i = 0; i < createdNodes.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = createdNodes[i];
		auto n2 = createdNodes[i + 1];
		auto f = faces.create(n0, n1, n2);
	}
}



void PolygonMesh::create(const TriangleCurve3d<float>& curve, const int id)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Vertex*>> createdNodes;

	std::vector<Vertex*> createNodes;
	std::vector<TriFace*> createFaces;

	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Vertex*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Vertex* node = createVertex(curve.get(i, j));
			ns.push_back(node);
			createNodes.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j];
			auto n2 = createdNodes[i][j + 1];
			auto f = faces.create(n0, n1, n2);
			createFaces.push_back(f);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j + 1];
			auto n2 = createdNodes[i - 1][j + 1];
			auto f = faces.create(n0, n1, n2);
			createFaces.push_back(f);
		}
	}
}



void PolygonMesh::cleaning()
{

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

void PolygonMesh::splitByNode(TriFace* f)
{
	const auto& es = f->toEdges();
	std::vector<Vertex*> startPoints;
	std::vector<Vertex*> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e.getStart());
		midPoints.push_back( createVertex(e.getMidPoint()) );
	}
	f->getV2()->moveTo(midPoints[0]->getPosition());
	f->getV3()->moveTo(midPoints[1]->getPosition());
	createFace(midPoints[0], startPoints[1], midPoints[1]);
	createFace(midPoints[1], startPoints[2], midPoints[2]);
	createFace(midPoints[0], startPoints[1], midPoints[2]);
}
