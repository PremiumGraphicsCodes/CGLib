#include "stdafx.h"
#include "PolygonFactory.h"
#include "NodeGrid.h"


using namespace Crystal::Math;
using namespace Crystal::Core;

PolygonFactory::PolygonFactory()
{
}

PolygonFactory::~PolygonFactory()
{
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

void PolygonFactory::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< Face* > fs;
	auto origin = vertices[0];
	for (size_t i = 1; i < vertices.size() - 1; i++) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		fs.push_back( faces.create(origin, v1, v2));
		v1->addFace( fs.back() );
		v2->addFace( fs.back() );
	}
}


void PolygonFactory::add(const Curve3d<float>& curve)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = vertices.create(pos, normal);
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
		faces.create(n0, n1, n2);
	}
}

void PolygonFactory::add(const CircularCurve3d<float>& curve)
{
	Vertex* centerNode = vertices.create(curve.getCenter().getPosition());

	std::vector<Vertex*> createdNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		Vertex* node = vertices.create(curve.get(i));
		createdNodes.push_back(node);
	}
	for (int i = 0; i < createdNodes.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = createdNodes[i];
		auto n2 = createdNodes[i + 1];
		auto f = faces.create(n0, n1, n2);
	}
	{
		auto n0 = centerNode;
		auto n1 = createdNodes.back();
		auto n2 = createdNodes.front();
		auto f = faces.create(n0, n1, n2);

	}
}

void PolygonFactory::add(const TriangleCurve3d<float>& curve)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Vertex*>> createdNodes;

	std::vector<Vertex*> createNodes;
	std::vector<Face*> createFaces;

	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Vertex*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Vertex* node = vertices.create(curve.get(i, j));
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

void PolygonFactory::splitByCenter(PolygonMesh* polygon,Face* f)
{
	Vertex* center = vertices.create(f->getCenterPoint());
	f->replace(f->getV2(), center);
	faces.create(f->getV1(), f->getV2(), center);
	faces.create(f->getV2(), f->getV1(), center);
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


PolygonMesh* PolygonFactory::create(const int id)
{
	return new PolygonMesh(vertices.get(), faces.get(), id);
}
