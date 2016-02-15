#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Bone::Bone(Joint* origin, Joint* dest) :
	origin(origin),
	dest(dest)
{}

void Bone::addChild(Bone* child)
{
	children.push_back(child);
}


float Bone::getLength() const
{
	return toLine().getLength();
}

Line3d<float> Bone::toLine() const
{
	return Line3d<float>(origin->getPosition(), dest->getPosition());
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
