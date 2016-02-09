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
	const float length = this->getLength();
	std::vector<Particle> particles;
	const Particle originParticle = origin->toParticle();
	const Particle destParticle = dest->toParticle();
	for (float l = 0.0f; l <= length; l += divideLength) {
		const float ratio = l / length;
		particles.emplace_back( originParticle.createBlended(destParticle, ratio) );
	}
	return particles;
}
