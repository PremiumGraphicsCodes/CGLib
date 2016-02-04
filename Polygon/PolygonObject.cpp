#include "PolygonObject.h"

#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



PolygonObject::~PolygonObject()
{
	clear();
}

VectorId* PolygonObject::createPosition(const Vector3d<float>& position)
{
	return positions.create(position);
}

VectorId* PolygonObject::createNormal(const Vector3d<float>& normal)
{
	return normals.create(normal);
}

VectorId* PolygonObject::createTexCoord(const Vector3d<float>& texCoord)
{
	return texCoords.create(texCoord);
}

Vertex* PolygonObject::createVertex(VectorId* position, VectorId* normal, VectorId* texCoord)
{
	return vertices.create(position, normal, texCoord);
}

Vertex* PolygonObject::createVertexFromIndices(const int positionIndex, const int normalIndex, const int texIndex)
{
	auto p = positions.get(positionIndex);
	VectorId* n = nullptr;
	if (normalIndex > -1) {
		n = normals.get(normalIndex);
	}
	VectorId* t = nullptr;
	if (texIndex > -1) {
		auto t = texCoords.get(texIndex);
	}
	return vertices.create(p, n, t);
}



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
	}
	return fs;
}


void PolygonObject::add(const Triangle<float>& triangle)
{
	auto n = createNormal( triangle.getNormal() );
	auto p1 = createPosition(triangle.getv0());
	auto p2 = createPosition(triangle.getv1());
	auto p3 = createPosition(triangle.getv2());

	auto v1 = vertices.create( p1, n );
	auto v2 = vertices.create( p2, n );
	auto v3 = vertices.create( p3, n );
	auto f = createFace(v1, v2, v3);
	v1->f = (f);
	v2->f = (f);
	v3->f = (f);
}


void PolygonObject::clear()
{
	positions.clear();
	normals.clear();
	texCoords.clear();
	vertices.clear();
	faces.clear();
}
