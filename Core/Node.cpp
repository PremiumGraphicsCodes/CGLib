#include "stdafx.h"
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


Node::Node(Vertex* v)
{
	vertices.push_back(v);
}

void Node::add(Vertex* v)
{
	vertices.push_back(v);
}

Point3d<float> Node::merge()
{
	const float size = static_cast<float>(vertices.size());
	Vector3d<float> position(0, 0, 0);
	Vector3d<float> normal(0, 0, 0);
	Vector2d<float> param(0, 0);
	for (auto v : vertices) {
		position += ( v->getPosition() / size );
		normal += ( v->getNormal() / size );
		param += (v->getParameter() / size);
	}
	normal.normalize();
	return Point3d<float>(position, normal, param);
}
