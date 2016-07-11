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
		v1->setFace( fs.back() );
		v2->setFace( fs.back() );
	}
	return fs;
}


void PolygonMesh::add(const Triangle3d<float>& triangle)
{
	auto n = triangle.getNormal();
	auto p1 = triangle.getv0();
	auto p2 = triangle.getv1();
	auto p3 = triangle.getv2();

	auto v1 = vertices.create( p1, n );
	auto v2 = vertices.create( p2, n );
	auto v3 = vertices.create( p3, n );
	auto f = createFace(v1, v2, v3);
	v1->setFace( f );
	v2->setFace( f );
	v3->setFace( f );
}



void PolygonMesh::add(const Quad<float>& quad)
{
	auto n = quad.getNormal();
	auto p1 = quad.getPositions()[0];
	auto p2 = quad.getPositions()[1];
	auto p3 = quad.getPositions()[2];
	auto p4 = quad.getPositions()[3];

	auto v1 = vertices.create(p1, n);
	auto v2 = vertices.create(p2, n);
	auto v3 = vertices.create(p3, n);
	auto v4 = vertices.create(p4, n);
	auto f = createFaces({ v1, v2, v3, v4 });
}

void PolygonMesh::add(const Box3d<float>& box)
{
	const auto& center = box.getCenter();
	const auto minx = box.getMinX();
	const auto miny = box.getMinY();
	const auto minz = box.getMinZ();
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();

	std::array< Vector3d<float>, 8 > ps = {
		Vector3d<float>(minx, miny, minz),
		Vector3d<float>(maxx, miny, minz),
		Vector3d<float>(maxx, maxy, minz),
		Vector3d<float>(minx, maxy, minz),
		Vector3d<float>(minx, miny, maxz),
		Vector3d<float>(maxx, miny, maxz),
		Vector3d<float>(maxx, maxy, maxz),
		Vector3d<float>(minx, maxy, maxz) };

	std::array< Vector3d<float>, 8 > ns;
	for (int i = 0; i < 8; ++i) {
		ns[i] = Vector3d<float>(ps[i] - center).normalized();
	}

	for (int i = 0; i < 8; ++i) {
		vertices.create(ps[i], ns[i]);
	}

	// near
	createFace(vertices[2], vertices[1], vertices[0]);
	createFace(vertices[0], vertices[3], vertices[2]);

	// far
	createFace(vertices[4], vertices[5], vertices[6]);
	createFace(vertices[6], vertices[7], vertices[4]);

	// right
	createFace(vertices[5], vertices[1], vertices[6]);
	createFace(vertices[6], vertices[1], vertices[2]);

	// left
	createFace(vertices[7], vertices[3], vertices[4]);
	createFace(vertices[3], vertices[0], vertices[4]);


	// top
	createFace(vertices[6], vertices[2], vertices[3]);
	createFace(vertices[7], vertices[6], vertices[3]);


	// bottom
	createFace(vertices[0], vertices[1], vertices[5]);
	createFace(vertices[0], vertices[5], vertices[4]);


	//createFace(vertices)

}

void PolygonMesh::add(const Sphere<float>& sphere, const int udiv, const int vdiv)
{
	;
}

#include "../Math/Curve3d.h"

void PolygonMesh::add(const Cone<float>& cone, const int div)
{
	const auto howMany = 360.0 / div;
	for (int i = 0; i < howMany; ++i) {
		;
	}
}


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

/*
#include "NodeGrid.h"

void PolygonMesh::create(const Curve3d<float>& curve, const int id = -1)
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

//void create(const Math::CircularCurve3d<float>& curve, const int id = -1);

//void create(const Math::TriangleCurve3d<float>& curve, const int id = -1);
*/