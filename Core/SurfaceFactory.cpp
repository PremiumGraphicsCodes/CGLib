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
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = nodes.create(Point3d<float>(pos, normal));
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
		auto v1 = t.get()[0];
		auto v2 = t.get()[1];
		auto v3 = t.get()[2];
		createTriangleFace(v1, v2, v3);
	}
	return create(id);
}




Surface* SurfaceFactory::create(const CircularCurve3d<float>& curve, const int id)
{
	Node* centerNode = nodes.create(curve.getCenter());

	std::vector<Node*> createNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		Node* node = nodes.create(curve.get(i));
		createNodes.push_back(node);
	}
	for (int i = 0; i < createNodes.size() - 1; ++i) {
		auto v0 = centerNode;
		auto v1 = createNodes[i];
		auto v2 = createNodes[i + 1];
		createTriangleFace(v0, v1, v2);
	}
	return create(id);
}

Surface* SurfaceFactory::create(const TriangleCurve3d<float>& curve, const int id)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Node*>> createdNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Node*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Node* node = nodes.create(curve.get(i, j));
			ns.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j];
			auto v2 = createdNodes[i][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j + 1];
			auto v2 = createdNodes[i - 1][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	return create(id);
}

Surface* SurfaceFactory::create(const int id)
{
	auto s = new Surface(nodes.get(), edges.get(), faces.get(), id);
	surfaces.push_back(s);
	return s;
}

Face* SurfaceFactory::createTriangleFace(Node* n1, Node* n2, Node* n3)
{
	auto e1 = edges.create(n1, n2);
	auto e2 = edges.create(n2, n3);
	auto e3 = edges.create(n3, n1);
	return faces.create(e1, e2, e3);
}

void SurfaceFactory::merge(SurfaceFactory& rhs)
{
	nodes.merge(rhs.nodes);
	edges.merge(rhs.edges);
	faces.merge(rhs.faces);
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

