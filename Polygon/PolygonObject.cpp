#include "PolygonObject.h"

#include "Vertex.h"
#include "Face.h"

#include "../Math/Sphere.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



PolygonObject::~PolygonObject()
{
	clear();
}


Vertex* PolygonObject::createVertex(Vector3d<float> position, Vector3d<float> normal, Vector3d<float> texCoord)
{
	return vertices.create(position, normal, texCoord);
}

Vertex* PolygonObject::findVertexById(const unsigned int id) const
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



Face* PolygonObject::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	return faces.create(v1, v2, v3);
}

Face* PolygonObject::createFace(const int vindex1, const int vindex2, const int vindex3)
{
	auto v1 = vertices[vindex1];
	auto v2 = vertices[vindex2];
	auto v3 = vertices[vindex3];
	return createFace(v1, v2, v3);
}

std::list< Face* > PolygonObject::createFaces(const std::vector<int>& ids)
{
	std::list< Face* > fs;
	const auto origin = ids[0];
	for (size_t i = 1; i < ids.size()-1; i++) {
		auto id1 = ids[i];
		auto id2 = ids[i + 1];
		fs.push_back( createFace(vertices[origin], vertices[id1], vertices[id2]) );
	}
	return fs;
}


std::list< Face* > PolygonObject::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< Face* > fs;
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


void PolygonObject::add(const Triangle<float>& triangle)
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



void PolygonObject::add(const Quad<float>& quad)
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

void PolygonObject::add(const Box3d<float>& box)
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
		ns[i] = Vector3d<float>(ps[i] - center).getNormalized();
	}

	for (int i = 0; i < 8; ++i) {
		vertices.create(ps[i], ns[i]);
	}

	createFace(vertices[2], vertices[1], vertices[0]);
	createFace(vertices[0], vertices[3], vertices[2]);

	createFace(vertices[4], vertices[5], vertices[6]);
	createFace(vertices[6], vertices[7], vertices[4]);

	createFace(vertices[5], vertices[1], vertices[6]);
	createFace(vertices[6], vertices[1], vertices[2]);

	createFace(vertices[7], vertices[3], vertices[4]);
	createFace(vertices[3], vertices[0], vertices[4]);

	createFace(vertices[6], vertices[2], vertices[3]);
	createFace(vertices[3], vertices[7], vertices[2]);

	createFace(vertices[0], vertices[1], vertices[5]);
	createFace(vertices[0], vertices[5], vertices[4]);

	//createFace(vertices)

}

void PolygonObject::add(const Sphere<float>& sphere, const int udiv, const int vdiv)
{
	;
}

void PolygonObject::merge(PolygonObject* rhs)
{
	this->vertices.merge(rhs->vertices);
	this->faces.merge(rhs->faces);
}

void PolygonObject::clear()
{
	//positions.clear();
	//normals.clear();
	//texCoords.clear();
	vertices.clear();
	faces.clear();
}

#include "../Math/Matrix4d.h"

void PolygonObject::transform(const Matrix4d<float>& matrix)
{
	for (auto v : vertices) {
		v->transform(matrix);
	}
}

PolygonObject* PolygonObject::clone(const unsigned int id)
{
	PolygonObject* newPolygon = new PolygonObject(id);
	for (auto v : vertices) {
		newPolygon->createVertex( v->getPosition(), v->getNormal(), v->getTexCoord());
	}
	for (auto f : faces) {
		newPolygon->createFace(f->getV1()->getId(), f->getV2()->getId(), f->getV3()->getId());
	}
	return newPolygon;
}
