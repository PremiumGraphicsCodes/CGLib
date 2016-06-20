#include "stdafx.h"
#include "Surface.h"
#include "Edge.h"
#include "Node.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Surface::Surface() :
	id(-1),
	nextNodeId(0),
	nextEdgeId(0),
	nextFaceId(0)
{
}

Surface::Surface(const Curve3d<float>& curve, const int id) :
	id(id),
	nextNodeId(0),
	nextEdgeId(0),
	nextFaceId(0)
{
	add(curve);
}

#include "../Util/Array2d.h"
#include "NodeGrid.h"

void Surface::add(const Curve3d<float>& curve)
{
	//Array2d<Node*> grid(curve.getUNumber(), curve.getVNumber());
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			Node* node = new Node(pos, normal, nextNodeId++);
			grid.set(u, v, node);
			nodes.push_back(node);
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
		Edge* e1 = new Edge(v1, v2, nextEdgeId++);
		Edge* e2 = new Edge(v2, v3, nextEdgeId++);
		Edge* e3 = new Edge(v3, v1, nextEdgeId++);

		Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);
		edges.push_back(e1);
		edges.push_back(e2);
		edges.push_back(e3);

		faces.push_back(f1);
	}

	/*
	for (int u = 0; u < curve.getUNumber() - 1; ++u) {
		for (int v = 0; v < curve.getVNumber() - 1; ++v) {
			auto v1 = grid.get(u, v);
			auto v2 = grid.get(u + 1, v);
			auto v3 = grid.get(u + 1, v + 1);
			auto v4 = grid.get(u, v + 1);

			Edge* e1 = new Edge(v1, v2, nextEdgeId++);
			Edge* e2 = new Edge(v2, v3, nextEdgeId++);
			Edge* e3 = new Edge(v3, v1, nextEdgeId++);

			Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);

			Edge* e4 = new Edge(v1, v3, nextEdgeId++);
			Edge* e5 = new Edge(v3, v4, nextEdgeId++);
			Edge* e6 = new Edge(v4, v1, nextEdgeId++);

			Face* f2 = new Face({ e4, e5, e6 }, nextFaceId++);

			edges.push_back(e1);
			edges.push_back(e2);
			edges.push_back(e3);
			edges.push_back(e4);
			edges.push_back(e5);
			edges.push_back(e6);

			faces.push_back(f1);
			faces.push_back(f2);
		}
	}

	{

		const auto u = curve.getUNumber() - 1;
		const auto v = curve.getVNumber() - 1;
		auto v1 = grid.get(u, v);
		auto v2 = grid.get(0, v);//grid.get(u + 1, v);
		auto v3 = grid.get(0, 0);
			auto v4 = grid.get(u, 0);

			Edge* e1 = new Edge(v1, v2, nextEdgeId++);
			Edge* e2 = new Edge(v2, v3, nextEdgeId++);
			Edge* e3 = new Edge(v3, v1, nextEdgeId++);

			Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);

			Edge* e4 = new Edge(v1, v3, nextEdgeId++);
			Edge* e5 = new Edge(v3, v4, nextEdgeId++);
			Edge* e6 = new Edge(v4, v1, nextEdgeId++);

			Face* f2 = new Face({ e4, e5, e6 }, nextFaceId++);

			edges.push_back(e1);
			edges.push_back(e2);
			edges.push_back(e3);
			edges.push_back(e4);
			edges.push_back(e5);
			edges.push_back(e6);

			faces.push_back(f1);
			faces.push_back(f2);
	}

	*/

}

void Surface::add(const CircularCurve3d<float>& curve)
{
	const auto center = curve.getCenter();
	Node* centerNode = new Node(center.getPosition(), center.getNormal(), nextNodeId++);
	nodes.push_back(centerNode);

	std::vector<Node*> createNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		const auto& pos = curve.get(i).getPosition();
		const auto& normal = curve.get(i).getNormal();

		Node* node = new Node(pos, normal, nextNodeId++);
		createNodes.push_back(node);
		nodes.push_back(node);
	}
	for (int i = 0; i < createNodes.size()-1; ++i) {
		auto v0 = centerNode;
		auto v1 = createNodes[i];
		auto v2 = createNodes[i + 1];
		Edge* e1 = new Edge(v0, v1, nextEdgeId++);
		Edge* e2 = new Edge(v1, v2, nextEdgeId++);
		Edge* e3 = new Edge(v2, v0, nextEdgeId++);
		Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);
		edges.push_back(e1);
		edges.push_back(e2);
		edges.push_back(e3);
		faces.push_back(f1);
	}
}



Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
	for (auto n : nodes) {
		delete n;
	}
	nodes.clear();
}

std::vector<unsigned int> Surface::toIndices() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back( e->getStart()->getId() );
		}
		//indices.push_back( edges.back()->getEnd()->getId() );
	}
	return indices;
}

void Surface::move(const Vector3d<float>& v)
{
	for (auto n : nodes) {
		n->move(v);
	}
}

void Surface::rotate(const Quaternion<float>& q)
{
	const auto& center = getCenter();
	move(-center);
	for (auto n : nodes) {
		n->transform(q.toMatrix());
	}
	move(center);
}

Vector3d<float> Surface::getCenter() const
{
	Vector3d<float> center;
	for (auto n : nodes) {
		center += n->getPosition() / nodes.size();
	}
	return center;
}
