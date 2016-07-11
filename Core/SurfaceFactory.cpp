#include "stdafx.h"
#include "SurfaceFactory.h"

#include "../Util/Array2d.h"
#include "NodeGrid.h"
#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

SurfaceFactory::SurfaceFactory(NodeCollection& nodes, EdgeCollection& edges, FaceCollection_& faces)
{
	this->nodes.merge(nodes);
	this->edges.merge(edges);
	this->faces.merge(faces);
}


SurfaceFactory::~SurfaceFactory()
{
	clear();
}

void SurfaceFactory::clear()
{
	nodes.clear();
	edges.clear();
	faces.clear();
}

Surface* SurfaceFactory::create(const Curve3d<float>& curve, const int id)
{
	std::vector<Node*> createNodes;
	std::vector<Edge*> createEdges;
	std::vector<Face*> createFaces;


	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = nodes.create(Point3d<float>(pos, normal));
			createNodes.push_back(n);
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
		auto e1 = edges.create(n0, n1);
		auto e2 = edges.create(n1, n2);
		auto e3 = edges.create(n2, n0);
		auto f = faces.create(e1, e2, e3);
		createEdges.push_back(e1);
		createEdges.push_back(e2);
		createEdges.push_back(e3);
		e1->connect(e2);
		e2->connect(e3);
		e3->connect(e1);
		assert(f->isConnected());
		createFaces.push_back(f);
	}
	return create(id, createNodes, createEdges, createFaces);
}




Surface* SurfaceFactory::create(const CircularCurve3d<float>& curve, const int id)
{
	Node* centerNode = nodes.create(curve.getCenter());

	std::vector<Node*> createNodes;
	std::vector<Edge*> createEdges;
	std::vector<Face*> createFaces;

	for (int i = 0; i < curve.getSize(); ++i) {
		Node* node = nodes.create(curve.get(i));
		createNodes.push_back(node);
	}
	for (int i = 0; i < createNodes.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = createNodes[i];
		auto n2 = createNodes[i + 1];
		auto e1 = edges.create(n0, n1);
		auto e2 = edges.create(n1, n2);
		auto e3 = edges.create(n2, n0);
		auto f = faces.create(e1, e2, e3);
		createEdges.push_back(e1);
		createEdges.push_back(e2);
		createEdges.push_back(e3);
		e1->connect(e2);
		e2->connect(e3);
		e3->connect(e1);
		assert(f->isConnected());

		createFaces.push_back(f);
	}
	return create(id, createNodes, createEdges, createFaces);
}

Surface* SurfaceFactory::create(const TriangleCurve3d<float>& curve, const int id)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Node*>> createdNodes;

	std::vector<Node*> createNodes;
	std::vector<Edge*> createEdges;
	std::vector<Face*> createFaces;

	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Node*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Node* node = nodes.create(curve.get(i, j));
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
			auto e1 = edges.create(n0, n1);
			auto e2 = edges.create(n1, n2);
			auto e3 = edges.create(n2, n0);
			auto f = faces.create(e1, e2, e3);
			createEdges.push_back(e1);
			createEdges.push_back(e2);
			createEdges.push_back(e3);
			e1->connect(e2);
			e2->connect(e3);
			e3->connect(e1);
			assert(f->isConnected());

			createFaces.push_back(f);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j + 1];
			auto n2 = createdNodes[i - 1][j + 1];
			auto e1 = edges.create(n0, n1);
			auto e2 = edges.create(n1, n2);
			auto e3 = edges.create(n2, n0);
			auto f = faces.create(e1, e2, e3);
			e1->connect(e2);
			e2->connect(e3);
			e3->connect(e1);
			assert(f->isConnected());

			createEdges.push_back(e1);
			createEdges.push_back(e2);
			createEdges.push_back(e3);
			createFaces.push_back(f);
		}
	}
	return create(id, createNodes, createEdges, createFaces);
}

Surface* SurfaceFactory::create(const int id, const std::vector<Node*>& nodes, const std::vector<Edge*>& edges, const std::vector<Face*>& faces)
{
	std::list<Node*> ns(nodes.begin(), nodes.end());
	std::list<Edge*> es(edges.begin(), edges.end());
	std::list<Face*> fs(faces.begin(), faces.end());
	auto s = new Surface(ns, es, fs, id);
	surfaces.push_back(s);
	return s;
}

/*
Face* SurfaceFactory::createTriangleFace(Node* n1, Node* n2, Node* n3)
{
	auto e1 = edges.create(n1, n2);
	auto e2 = edges.create(n2, n3);
	auto e3 = edges.create(n3, n1);
	return faces.create(e1, e2, e3);
}
*/

void SurfaceFactory::merge(SurfaceFactory& rhs)
{
	nodes.merge(rhs.nodes);
	edges.merge(rhs.edges);
	faces.merge(rhs.faces);
}

void SurfaceFactory::remove(Face* f)
{
	findSurface(f)->remove(f);
	/*
	const auto edges = f->getEdges();
	for (auto e : edges) {
		remove(e);
	}
	*/
	faces.remove(f);
}

void SurfaceFactory::remove(Edge* e)
{
	auto s = findSurface(e);
	s->remove(e);
	edges.remove(e);
}

void SurfaceFactory::remove(Node* n)
{
	findSurface(n)->remove(n);
	nodes.remove(n);
}


Surface* SurfaceFactory::findSurfaceById(const int id)
{
	for (auto s : surfaces) {
		if (s->getId() == id) {
			return s;
		}
	}
	return nullptr;
}

Edge* SurfaceFactory::findEdgeById(const int id) const
{
	return edges.findById(id);
}

Node* SurfaceFactory::findNodeById(const int id) const
{
	return nodes.findById(id);
}

Face* SurfaceFactory::findFaceById(const int id) const
{
	return faces.findById(id);
}

Surface* SurfaceFactory::findSurface(Edge* e) const
{
	for (auto s : surfaces) {
		if (s->has(e)) {
			return s;
		}
	}
	return nullptr;
}

Surface* SurfaceFactory::findSurface(Face* f) const
{
	for (auto s : surfaces) {
		if (s->has(f)) {
			return s;
		}
	}
	return nullptr;
}

Surface* SurfaceFactory::findSurface(Node* e) const
{
	for (auto s : surfaces) {
		if (s->has(e)) {
			return s;
		}
	}
	return nullptr;
}

std::list<Face*> SurfaceFactory::findFaces(Edge* e) const
{
	return faces.findByEdge(e);
}

void SurfaceFactory::renumber()
{
	nodes.renumber();
	edges.renumber();
	faces.renumber();
	int nextId = 0;
	for (auto s : surfaces) {
		s->setId(nextId++);
	}
}
