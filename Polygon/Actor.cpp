#include "Actor.h"
#include "Particle.h"
#include "ParticleObject.h"
#include "Joint.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



Bone::Bone(Joint* origin, Joint* dest) :
	origin(origin),
	dest(dest)
{}

/*
std::vector<Vector3d<float>> Bone::toPositions(const int howMany) const
{
	Line3d<float> line(origin->getPosition(), dest->getPosition());
	return line.toPositionsByLength(howMany);
}

std::vector<float> Bone::toValues(const int howMany) const
{
	dest->get
}
*/

float Bone::getLength() const
{
	Line3d<float> line(origin->getPosition(), dest->getPosition());
	return line.getLength();
}

/*
ParticleObject Bone::toParticleObject(const float divideLength)
{
	return positions;
}
*/

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


Joint* Actor::createJoint(const Vector3d<float>& pos, const float radius, const float thickness)
{
	auto j = new Joint(pos, radius, thickness);
	joints.push_back(j);
	return j;
}


Bone* Actor::createBone(Joint* j1, Joint* j2)
{
	auto b = new Bone(j1, j2);
	bones.push_back(b);
	return b;
}
