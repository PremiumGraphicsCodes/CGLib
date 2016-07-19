#include "stdafx.h"
#include "PolygonFactory.h"
#include "NodeGrid.h"
#include "Edge.h"


#include "Volume.h"
#include "OctTree.h"

#include "VolumeCell.h"
#include "ParticleObject.h"

#include "../Math/SPHKernel.h"


using namespace Crystal::Math;
using namespace Crystal::Core;

PolygonMesh* PolygonBuilder::build(int id)
{
	std::list<Vertex*> vs(vertices.begin(), vertices.end());
	std::list<Face*> fs(faces.begin(), faces.end());
	return new PolygonMesh(vs, fs, id);
}

PolygonBuilder::PolygonBuilder(const Volume& volume, float isolevel)
{
	const auto& triangles = volume.toTriangles(isolevel);
	std::list<Vertex*> vertices;
	std::list<Face*> faces;
	for (const auto& t : triangles) {
		auto v1 = new Vertex(t.getv0(), t.getNormal(), 0);
		auto v2 = new Vertex(t.getv1(), t.getNormal(), 0);
		auto v3 = new Vertex(t.getv2(), t.getNormal(), 0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		createFace(v1, v2, v3);
	}
	VertexCollection vc(vertices);
	vc.sort();
	auto vv = vc.get();
	this->vertices = std::vector<Vertex*>( vv.begin(), vv.end());
}


PolygonFactory::PolygonFactory() :
	nextId(0)
{
}

PolygonFactory::~PolygonFactory()
{
	clear();
}

void PolygonFactory::add(PolygonMesh* p)
{
	auto vs = p->getVertices();
	this->vertices.merge(vs);
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

void PolygonBuilder::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< Face* > fs;
	auto origin = vertices[0];
	for (size_t i = 1; i < vertices.size() - 1; i++) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		Edge* e1 = new Edge(origin, v1);
		Edge* e2 = new Edge(v1, v2);
		Edge* e3 = new Edge(v2, origin);

		fs.push_back( new Face(e1, e2, e3));
		v1->addFace( fs.back() );
		v2->addFace( fs.back() );
	}
}


PolygonBuilder::PolygonBuilder(const Curve3d<float>& curve)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();
			auto n = new Vertex(pos, normal, -1);
			vertices.push_back(n);
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
		createFace( n0, n1, n2 );
	}
}

PolygonBuilder::PolygonBuilder(const CircularCurve3d<float>& curve)
{
	Vertex* centerNode = new Vertex(curve.getCenter().getPosition(), -1);

	for (int i = 0; i < curve.getSize(); ++i) {
		vertices.push_back( new Vertex(curve.get(i)) );
	}
	for (int i = 0; i < vertices.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = vertices[i];
		auto n2 = vertices[i + 1];
		createFace( n0, n1, n2);
	}
	{
		auto n0 = centerNode;
		auto n1 = vertices.back();
		auto n2 = vertices.front();
		createFace(n0, n1, n2);
		
	}
	vertices.push_back(centerNode);

}

PolygonBuilder::PolygonBuilder(const TriangleCurve3d<float>& curve)
{
	std::vector< TriangleCell > cells;
	std::vector<std::vector<Vertex*>> createdNodes;

	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Vertex*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			auto node = new Vertex( curve.get(i, j) );
			vertices.push_back(node);
			ns.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j];
			auto n2 = createdNodes[i][j + 1];
			createFace(n0, n1, n2);
			//createFaces.push_back(f);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j + 1];
			auto n2 = createdNodes[i - 1][j + 1];
			createFace(n0, n1, n2);
			//createFaces.push_back(f);
		}
	}
}

void PolygonFactory::splitByCenter(PolygonMesh* polygon,Face* f)
{
	addVertex(f, f->getCenterPoint());
}

void PolygonFactory::addVertex(Face* f, const Point3d<float>& point)
{
	auto v = vertices.create(point);
	auto f1 = createFace(f->getV1(), f->getV2(), v);
	auto f2 = createFace(f->getV2(), f->getV3(), v);
	f->replace(f->getV2(), v);

	auto polygon = find(f);
	polygon->add(v);
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
	this->edges.merge(EdgeCollection(edges));
	this->faces.merge(FaceCollection(faces));
	polygons.push_back(p);
	return p;
}

PolygonMesh* PolygonFactory::create(VertexCollection& vertices, FaceCollection& faces)
{
	auto p = new PolygonMesh(vertices.get(), faces.get(), nextId++);
	this->vertices.merge(vertices);
	this->faces.merge(faces);
	polygons.push_back(p);
	return p;
}

namespace {
	Crystal::Math::SPHKernel<float> kernel;
	float getPoly6Kernel(const float distance, const float effectLength) {
		return kernel.getPoly6Kernel(distance, effectLength);
	}
}



PolygonBuilder::PolygonBuilder(const ParticleObject& particle, const float isolevel, const int levelOfDetail, const Space3d<float>& space)
{
	OctTree tree(space);
	const auto& particles = particle.getParticles();
	for (auto& p : particles) {
		tree.add(p);
	}
	std::vector<VolumeCell> cells;
	const auto& children = tree.createChildren(levelOfDetail);//Vector3d<float>(effectLength,effectLength,effectLength));
	for (const auto& c : children) {
		const auto& box = c.getBoundingBox();
		const auto& poss = box.toSpace().toArray();
		std::array<float, 8> values;
		values.fill(0.0f);
		for (int i = 0; i < 8; ++i) {
			for (const auto& particle : c.getParticles()) {
				const auto dist2 = poss[i].getDistanceSquared(particle->getPosition());
				const auto radiusSquared = particle->getBoundingRadius() * particle->getBoundingRadius();
				if (dist2 < radiusSquared) {
					//const auto value = kernel.getPoly6Kernel(std::sqrt(dist2), std::sqrt(radiusSquared)) * particle->getDensity();
					const auto diff = poss[i] - particle->getPosition();
					const auto& m = particle->getMatrix().getInverse(); //getScaled(1.0 / particle->getBoundingRadius());
																		//				const auto mm = Matrix3d<float>(1.0 / particle->getRadii().getX(), 0, 0, 0, 1.0 / particle->getRadii().getY(), 0, 0, 0, 1.0 / particle->getRadii().getZ());
					const auto value = kernel.getCubicSpline(diff, m) * particle->getDensity();
					values[i] += value;
				}
			}
		}
		VolumeCell cell(c.getBoundingBox().toSpace(), values);
		cells.emplace_back(cell);
	}
	std::vector<Triangle3d<float>> triangles;
	for (const auto& cell : cells) {
		const auto& ts = cell.toTriangles(isolevel);
		triangles.insert(triangles.end(), ts.begin(), ts.end());
	}
	std::list<Vertex*> vertices;
	std::list<Face*> faces;
	for (const auto& t : triangles) {
		auto v1 = new Vertex(t.getv0(), t.getNormal(), 0);
		auto v2 = new Vertex(t.getv1(), t.getNormal(), 0);
		auto v3 = new Vertex(t.getv2(), t.getNormal(), 0);
		createFace(v1, v2, v3);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		//factory.create(t.toCurve3d());
	}
	VertexCollection vc(vertices);
	vc.sort();
	this->vertices = std::vector<Vertex*>(vc.begin(), vc.end());
	//newMesh->removeOverlappedVertices();
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
	auto vs = p->getVertices();
	for (auto v : vs) {
		vertices.remove(v);
	}
	auto fs = p->getFaces();
	for (auto f : fs) {
		faces.remove(f);
	}
	polygons.remove(p);
	delete p;
	renumber();
}

void PolygonFactory::remove(Face* f)
{
	auto polygon = find(f);
	polygon->remove(f);
	faces.remove(f);
	//findPo
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
	std::list<Face*> degenerateds;
	for (auto f : faces) {
		if (f->isDegenerated()) {
			degenerateds.push_back(f);
		}
	}
	for (auto f : degenerateds) {
		remove(f);
	}

	faces.renumber();
}

void PolygonBuilder::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = new Edge(v1, v2);
	auto e2 = new Edge(v2, v3);
	auto e3 = new Edge(v3, v1);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	auto f = new Face(e1, e2, e3);
	faces.push_back(f);
}

Face* PolygonFactory::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = edges.create(v1, v2);
	auto e2 = edges.create(v2, v3);
	auto e3 = edges.create(v3, v1);
	auto f = faces.create(e1, e2, e3);
	return f;
}