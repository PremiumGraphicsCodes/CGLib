#include "Face.h"

#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

float Face::getArea() const
{
	const auto v1 = edges[0]->getVector();
	const auto v2 = edges[1]->getVector();
	return v1.getOuterProduct(v2).getLength() * 0.5f;
}

Vector3d<float> Face::getNormal() const
{
	const auto v1 = edges[0]->getVector();
	const auto v2 = edges[1]->getVector();
	return v1.getOuterProduct(v2);
}
