#include "stdafx.h"
#include "Vertex.h"
#include "VertexCollection.h"
#include "EdgeCollection.h"
#include "PolygonBuilder.h"
#include "ParticleObject.h"
#include "PolygonMesh.h"
#include "Volume.h"
#include "VolumeCell.h"
#include "NodeGrid.h"
#include "OctTree.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

namespace {
	Crystal::Math::SPHKernel<float> kernel;
	float getPoly6Kernel(const float distance, const float effectLength) {
		return kernel.getPoly6Kernel(distance, effectLength);
	}
}


PolygonMesh* PolygonBuilder::build(int id)
{
	VertexCollection vc(vertices);
	vc.renumber();
	EdgeCollection ec(edges);
	ec.renumber();
	FaceCollection fc(faces);
	fc.renumber();
	return new PolygonMesh(fc.get(), id);
}

PolygonBuilder::PolygonBuilder(const std::vector<Vertex*>& vertices, const std::vector<Face*>& faces, const std::vector<Edge*>& edges) :
	vertices(vertices),
	faces(faces),
	edges(edges)
{
}


PolygonBuilder::PolygonBuilder(const Volume& volume, float isolevel)
{
	const auto& triangles = volume.toTriangles(isolevel);
	const auto divideLength = volume.getUnitLength().getX();
	create(triangles, divideLength);
}

#include "VertexSpaceHash.h"

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
	const auto divideLength = space.getLengths().getX() / std::pow(2, levelOfDetail);
	create(triangles, divideLength);
	//newMesh->removeOverlappedVertices();
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
		createFace(n0, n1, n2);
	}
}

PolygonBuilder::PolygonBuilder(const CircularCurve3d<float>& curve)
{
	Vertex* centerNode = new Vertex(curve.getCenter().getPosition(), -1);

	for (int i = 0; i < curve.getSize(); ++i) {
		vertices.push_back(new Vertex(curve.get(i)));
	}
	for (int i = 0; i < vertices.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = vertices[i];
		auto n2 = vertices[i + 1];
		createFace(n0, n2, n1);
	}
	{
		auto n0 = centerNode;
		auto n1 = vertices.back();
		auto n2 = vertices.front();
		createFace(n0, n2, n1);
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
			auto node = new Vertex(curve.get(i, j));
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
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j + 1];
			auto n2 = createdNodes[i - 1][j + 1];
			createFace(n0, n1, n2);
		}
	}
}

void PolygonBuilder::create(const std::vector< Triangle3d<float> >& triangles, const float divideLength)
{
	std::list<Vertex*> vertices;
	std::list<Vertex*> created;
	VertexSpaceHash hash(divideLength, triangles.size());
	for (const auto& t : triangles) {
		auto v1 = new Vertex(t.getv0(), t.getNormal(), 0);
		auto v2 = new Vertex(t.getv1(), t.getNormal(), 0);
		auto v3 = new Vertex(t.getv2(), t.getNormal(), 0);
		hash.add(v1);
		hash.add(v2);
		hash.add(v3);
		created.push_back(v1);
		created.push_back(v2);
		created.push_back(v3);
	}
	for (const auto& t : triangles) {
		auto v1 = hash.findSameStrictly(t.getv0());
		auto v2 = hash.findSameStrictly(t.getv1());
		auto v3 = hash.findSameStrictly(t.getv2());
		vertices.push_back(v1.front());
		vertices.push_back(v2.front());
		vertices.push_back(v3.front());
		createFace(v1.front(), v2.front(), v3.front());
	}
	vertices.sort();
	vertices.unique();
	created.sort();
	created.unique();
	std::list<Vertex*> garbages;
	std::set_difference(created.begin(), created.end(),
		vertices.begin(), vertices.end(),
		std::back_inserter(garbages));
	for (auto g : garbages) {
		delete g;
	}
	this->vertices = std::vector<Vertex*>(vertices.begin(), vertices.end());
}


void PolygonBuilder::createFaces(const std::vector<Vertex*>& vertices)
{
	auto origin = vertices[0];
	for (size_t i = 1; i < vertices.size() - 1; i++) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		createFace(origin, v1, v2);
	}
}

Face* PolygonBuilder::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = new Edge(v1, v2);
	auto e2 = new Edge(v2, v3);
	auto e3 = new Edge(v3, v1);
	e1->connect(e2);
	e2->connect(e3);
	e3->connect(e1);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	auto f = new Face(e1, e2, e3);
	e1->setFace(f);
	e2->setFace(f);
	e3->setFace(f);

	faces.push_back(f);
	return f;
}

void PolygonBuilder::merge(PolygonBuilder& rhs)
{
	vertices.insert(vertices.end(), rhs.vertices.begin(), rhs.vertices.end());
	faces.insert(faces.end(), rhs.faces.begin(), rhs.faces.end());
	edges.insert(edges.end(), rhs.edges.begin(), rhs.edges.end());
}

void PolygonBuilder::reverse(Face* f)
{
	auto& es = f->getEdges();
	for (auto e : es) {
		e->reverse();
	}
}
