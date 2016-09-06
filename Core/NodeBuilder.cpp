#include "stdafx.h"
#include "NodeBuilder.h"
#include "Vertex.h"
#include "VertexSpaceHash.h"
#include "Node.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

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
		return toHash(v1->getPosition()) < toHash(v2->getPosition());
	}

	bool isSame(Vertex* v1, Vertex* v2)
	{
		if (v1->getPosition() == v2->getPosition()) {
			v1->normalize(*v2);
			//delete v2;
			//v2 = nullptr;
			return true;
		}
		return false;
	}
}


NodeBuilder::NodeBuilder(const std::list<Vertex*>& vertices) :
	vertices(vertices)
{}

std::list<Node*> NodeBuilder::build(const float distance)
{
	const auto& bb = Util::getBoundingBox(vertices);
	const auto minLength = std::min<float>({ bb.getLength().getX(), bb.getLength().getY(), bb.getLength().getZ() });
	const auto hashSize = static_cast<int>(vertices.size());
	const auto divideLength = std::max<float>(minLength / 10.0f, distance);
	VertexSpaceHash space(divideLength, hashSize);
	for (auto v : vertices) {
		space.add(v);

	}
	std::list<Node*> nodes;

	for (auto iter = vertices.begin(); iter != vertices.end();) {
		auto v = *(iter);
		auto node = new Node();
		node->add(v);

		const auto& neighbors = space.getNeighbor(v);
		std::list<Vertex*> removes;
		for (auto n : neighbors) {
			if (n == v) {
				continue;
			}
			if (v->getPosition().getDistanceSquared(n->getPosition()) < distance * distance) {
				node->add(n);
				removes.push_back(n);
				continue;
			}
		}
		if (removes.empty()) {
			++iter;
		}
		else {
			for (auto v : removes) {
				auto i = std::find(vertices.begin(), vertices.end(), v);
				iter = vertices.erase(i);
				space.remove(v);
			}
		}
		nodes.push_back(node);
	}
	return nodes;
}
