#include "stdafx.h"
#include "PolygonFactory.h"
#include "Edge.h"
#include "PolygonBuilder.h"


#include "VolumeCell.h"
#include "ParticleObject.h"

#include "../Math/SPHKernel.h"


using namespace Crystal::Math;
using namespace Crystal::Core;



PolygonFactory::PolygonFactory() :
	nextId(0)
{
}

PolygonFactory::~PolygonFactory()
{
	clear();
}

PolygonFactory::PolygonFactory(VertexCollection& vertices)
{
	this->vertices.merge(vertices);
}


void PolygonFactory::add(PolygonMesh* p)
{
	auto fs = p->getFaces();
	this->faces.merge(FaceCollection(fs));
	polygons.push_back(p);
}


void PolygonFactory::clear()
{
	for (auto p : polygons) {
		delete p;
	}
	polygons.clear();
}


/*
std::list< Face* > PolygonFactory::createFaces(const std::vector<int>& ids)
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
*/



void PolygonFactory::splitByCenter(PolygonMesh* polygon,Face* f)
{
	addVertex(f, f->getCenterPoint());
}

void PolygonFactory::addVertex(Face* f, const Point3d<float>& point)
{
	auto e1 = f->getEdges()[1];
	auto e2 = f->getEdges()[2];
	auto v = vertices.create(point);

	auto f1 = createFace(f->getV1(), f->getV2(), v);
	auto f2 = createFace(f->getV2(), f->getV3(), v);

	e1->changeEnd(v);
	e2->changeStart(v);

	auto polygon = find(f);
	polygon->add(f1);
	polygon->add(f2);
	faces.renumber();
	edges.renumber();
	vertices.renumber();
}

void PolygonFactory::splitByBottom(PolygonMesh* polygon,Face* f)
{
	/*
	auto bottom = nodes.create(f->getEdges()[1]->getMidPoint());
	auto f2 = createTriangleFace(bottom, f->getEdges()[2]->getStart(), f->getEdges()[2]->getEnd());

	f->getEdges()[1]->changeEnd(bottom);
	f->getEdges()[2]->changeStart(bottom);
	f->getEdges()[2]->changeEnd(f->getEdges()[0]->getStart());
	assert(f->getArea() > 0);

	assert( f2->getArea() > 0);

	surface->add(faces.get());
	surface->add(nodes.get());
	surface->add(edges.get());
	SurfaceFactory fa(nodes, edges, faces);
	factory->merge(fa);
	for (auto f : surface->getFaces()) {
	assert(f->isConnected());
	}
	*/
}

void PolygonFactory::splitByNode(PolygonMesh* polygon, Face* f)
{
	/*
	const auto& es = f->toEdges();
	std::vector<Vertex*> startPoints;
	std::vector<Vertex*> midPoints;
	for (const auto& e : polygon->getE) {
		startPoints.push_back(e.getStart());
		midPoints.push_back(createVertex(e.getMidPoint()));
	}
	faces.create(midPoints[0], startPoints[1], midPoints[1]);
	faces.create(midPoints[1], startPoints[2], midPoints[2]);
	faces.create(midPoints[0], startPoints[1], midPoints[2]);
	f->getV2()->moveTo(midPoints[0]->getPosition());
	f->getV3()->moveTo(midPoints[1]->getPosition());
	*/
}


PolygonMesh* PolygonFactory::create(PolygonBuilder& builder)
{
	auto p = builder.build( nextId++);
	this->vertices.merge(VertexCollection(builder.vertices));
	this->edges.merge(EdgeCollection(builder.edges));
	this->faces.merge(FaceCollection(builder.faces));
	polygons.push_back(p);
	return p;
}

PolygonMesh* PolygonFactory::create(FaceCollection& faces)
{
	auto p = new PolygonMesh(faces.get(), nextId++);
	this->faces.merge(faces);
	polygons.push_back(p);
	return p;
}

PolygonMesh* PolygonFactory::findPolygonById(const int id)
{
	for (auto p : polygons) {
		if (p->getId() == id) {
			return p;
		}
	}
	return nullptr;
}

PolygonMesh* PolygonFactory::find(Face* f)
{
	for (auto p : polygons) {
		if (p->has(f)) {
			return p;
		}
	}
	return nullptr;
}

PolygonMesh* PolygonFactory::find(Vertex* v)
{
	/*
	for (auto p : polygons) {
		if (p->has(v)) {
			return p;
		}
	}
	*/
	return nullptr;
}

PolygonMesh* PolygonFactory::find(Edge* e)
{
	return find(e->getFace());
}


void PolygonFactory::merge(PolygonFactory& rhs)
{
	polygons.insert(polygons.end(), rhs.polygons.begin(), rhs.polygons.end());
	faces.merge(rhs.faces);
	vertices.merge(rhs.vertices);
	renumber();
	rhs.polygons.clear();
	rhs.faces.clear();
	rhs.vertices.clear();
}

void PolygonFactory::renumber()
{
	nextId = 0;
	for (auto p : polygons) {
		p->setId(nextId++);
	}
	vertices.renumber();
	faces.renumber();
}

void PolygonFactory::remove(PolygonMesh* p)
{
	if (p == nullptr) {
		return;
	}
	polygons.remove(p);
	delete p;
	renumber();
}

void PolygonFactory::remove(Face* f)
{
	auto polygon = find(f);
	if(polygon) {
		polygon->remove(f);
	}
	faces.remove(f);
}


void PolygonFactory::destory(Vertex* v)
{
	auto polygon = find(v);
	for (auto e : edges) {
		if (e->has(v)) {
			e->toDenerate();
		}
	}
}

void PolygonFactory::destory(Edge* e)
{
	auto v = e->getEnd();
	e->changeStart(v);
	cleaning();
}


void PolygonFactory::destory(Face* f)
{
	auto e = f->getEdges().front();
	auto polygon = find(f);
	if (polygon) {
		polygon->remove(f);
	}
}

void PolygonFactory::destory(PolygonMesh* polygon)
{
	auto faces = polygon->getFaces();
	for (auto f : faces) {
		destory(f);
	}
}


/*
PolygonMesh* PolygonFactory::find(Face* f)
{
	for (auto p : polygons) {
		if (p->has(f)) {
			return p;
		}
	}
	return nullptr;
}
*/
void PolygonFactory::simplify(PolygonMesh* p, int howMany)
{
	for (int i = 0; i < howMany; ++i) {
		auto edge = p->getShortestEdge();
		p->simplify(*edge);
	}
	cleaning();
}

void PolygonFactory::cleaning()
{
	auto df = faces.getDegenerateds();
	for (auto f : df) {
		this->destory(f);
	}
}

Face* PolygonFactory::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = edges.create(v1, v2);
	auto e2 = edges.create(v2, v3);
	auto e3 = edges.create(v3, v1);
	auto f = faces.create(e1, e2, e3);
	return f;
}

Edge* PolygonFactory::getShared(Edge* e)
{
	return edges.findReverse(e);
}


std::map<Vertex*, Vertex*> PolygonFactory::findDouble(PolygonMesh* lhs, PolygonMesh* rhs, float distance)
{
	auto vertices1 = lhs->getVertices();
	auto vertices2 = rhs->getVertices();
	std::map<Vertex*, Vertex*> map;
	for (auto v1 : vertices1) {
		for (auto v2 : vertices2) {
			auto p1 = v1->getPosition();
			auto p2 = v2->getPosition();
			if (p1.getDistanceSquared(p2) < distance * distance) {
				map[v1] = v2;
			}
		}
	}
	return map;
}


void PolygonFactory::mergeDouble(PolygonMesh* lhs, PolygonMesh* rhs, float distance)
{
	auto vertices1 = lhs->getVertices();
	auto vertices2 = rhs->getVertices();
	auto doubles = findDouble(lhs, rhs, distance);
	for (auto d : doubles) {
		auto v1 = d.first;
		auto v2 = d.second;
		auto edges2 = rhs->getEdges();
		for (auto e2 : edges2) {
			if (e2->getStart() == v2) {
				e2->changeStart(v1);
			}
			if (e2->getEnd() == v2) {
				e2->changeEnd(v1);
			}
		}
	}
}
