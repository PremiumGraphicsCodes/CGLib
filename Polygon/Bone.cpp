#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Bone::Bone(Joint* origin, Joint* dest, const unsigned int id) :
	origin(origin),
	dest(dest),
	thickness(1.0f),
	id(id)
{}

Bone::~Bone()
{
	clear();
}

void Bone::clear()
{
	for (auto c : children) {
		delete c;
	}
	children.clear();
}


Bone* Bone::createChild(Joint* childDest)
{
	auto b = new Bone(dest, childDest);
	children.push_back(b);
	return b;
}



float Bone::getLength() const
{
	return toLine().getLength();
}

Line3d<float> Bone::toLine() const
{
	return Line3d<float>(origin->getPosition(), dest->getPosition());
}


std::vector<Particle> Bone::toParticles(const float divideLength, const float density)
{
	const float length = this->getLength();
	std::vector<Particle> particles;
	const Particle originParticle = origin->toParticle(density);
	const Particle destParticle = dest->toParticle(density);
	for (float l = 0.0f; l <= length; l += divideLength) {
		const float ratio = l / length;
		particles.emplace_back( originParticle.createBlended(destParticle, ratio) );
	}
	return particles;
}
