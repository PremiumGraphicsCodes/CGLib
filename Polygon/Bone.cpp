#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Bone::Bone(Joint* origin, Joint* dest) :
	origin(origin),
	dest(dest)
{}

float Bone::getLength() const
{
	Line3d<float> line(origin->getPosition(), dest->getPosition());
	return line.getLength();
}

std::vector<Particle> Bone::toParticles(const float divideLength)
{
	std::vector<Particle> particles;
	return particles;
}
