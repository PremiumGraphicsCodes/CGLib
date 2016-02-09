#include "Actor.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Bone::Bone(Joint* origin, Joint* dest) :
	origin(origin),
	dest(dest)
{}

std::vector< Vector3d<float> > Bone::toPositions(const float divideLength)
{
	Line3d<float> line(origin->getPosition(), dest->getPosition());
	const auto& positions = line.toPositionsByLength(divideLength);
	return positions;
}

void Actor::clear()
{
	for (auto b : bones) {
		delete b;
	}
	bones.clear();
	for (auto j : joints) {
		delete j;
	}
	joints.clear();
}


Joint* Actor::createJoint(const Vector3d<float>& pos, const float thickness)
{
	auto j = new Joint(pos, thickness);
	joints.push_back(j);
	return j;
}


Bone* Actor::createBone(Joint* j1, Joint* j2)
{
	auto b = new Bone(j1, j2);
	bones.push_back(b);
	return b;
}
