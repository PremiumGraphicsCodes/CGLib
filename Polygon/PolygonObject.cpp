#include "PolygonObject.h"

#include "Vertex.h"
#include "TriangleFace.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

namespace {
	int toHash(const Vector3d<float>& pos)
	{
		const int p1 = 73856093;
		const int p2 = 19349663;
		const int p3 = 83492791;
		const int hashTableSize = 10000;
		const int x = static_cast<int>(pos.getX() * p1);
		const int y = static_cast<int>(pos.getY() * p2);
		const int z = static_cast<int>(pos.getZ() * p3);
		return  (x^y^z) % hashTableSize;
	}

	bool comp(Vertex* v1, Vertex* v2)
	{
		return toHash(v1->getPosition()->getVector()) < toHash(v2->getPosition()->getVector());
	}

	bool isSame(Vertex* v1, Vertex* v2)
	{
		if (v1->position == v2->position) {
			auto face = v2->f;
			face->replace(v2, v1);
			delete v2;
			return true;
		}
		return false;
	}
}


PolygonObject::~PolygonObject()
{
	clear();
}

bool PolygonObject::hasVertex(Vertex* v)
{
	return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
}

void PolygonObject::sortVertices()
{
	vertices.sort(::comp);
	vertices.unique(::isSame);
	int nextId = 0;
	for (auto v : vertices) {
		v->id = nextId++;
	}
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
	auto v = new Vertex();
	v->position = position;
	v->normal = normal;
	v->texCoord = texCoord;
	v->id = nextIndexId++;
	vertices.push_back(v);
	return v;
}

Vertex* PolygonObject::createVertexFromIndices(const int positionIndex, const int normalIndex, const int texIndex)
{
	auto p = positions.get(positionIndex);
	VectorId* n = nullptr;
	if (normalIndex != -1) {
		n = normals.get(normalIndex);
	}
	VectorId* t = nullptr;
	if (texIndex != -1) {
		auto t = texCoords.get(texIndex);
	}
	return createVertex(p, n, t);
}



TriangleFace* PolygonObject::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new TriangleFace(v1, v2, v3);
	faces.push_back(f);
	return f;
}

TriangleFace* PolygonObject::createFace(const int vindex1, const int vindex2, const int vindex3)
{
	std::vector<Vertex*> vs(vertices.begin(), vertices.end());
	auto v1 = vs[vindex1];
	auto v2 = vs[vindex2];
	auto v3 = vs[vindex3];
	return createFace(v1, v2, v3);
}

std::list< TriangleFace* > PolygonObject::createFaces(const std::vector<int>& ids)
{
	std::list< TriangleFace* > fs;
	std::vector<Vertex*> vs(vertices.begin(), vertices.end());
	const auto origin = ids[0];
	for (size_t i = 1; i < ids.size()-1; i++) {
		auto id1 = ids[i];
		auto id2 = ids[i + 1];
		fs.push_back( createFace(vs[origin], vs[id1], vs[id2]) );
	}
	return fs;
}


std::list< TriangleFace* > PolygonObject::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< TriangleFace* > fs;
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

	auto v1 = createVertex( p1, n );
	auto v2 = createVertex( p1, n );
	auto v3 = createVertex( p3, n );
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
	for (auto f : faces) {
		delete f;
	}
	faces.clear();

}
