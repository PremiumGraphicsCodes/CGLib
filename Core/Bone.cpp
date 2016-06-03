#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"
#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Bone::Bone(Joint* origin, Joint* dest, const float thickness, const unsigned int id) :
	origin(origin),
	dest(dest),
	thickness(thickness),
	id(id)
{}

Bone::~Bone()
{
	clear();
}

Bone* Bone::clone(const unsigned int newId) const
{
	return new Bone(origin, dest, thickness, newId);
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
	auto b = new Bone(dest, childDest, 1, 1);
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
	const float start = origin->getRadius() + divideLength * 0.5f;
	const float end = length - dest->getRadius();// - divideLength * 0.5f;
	for (float l = start ; l < end; l += divideLength) {
		const float ratio = l / length;
		particles.emplace_back( originParticle.createBlended(destParticle, ratio) );
	}
	return particles;
}

std::vector<AnisotoropicParticle> Bone::toAnisoParticles(const float divideLength, const float density)
{
	const float length = this->getLength();
	std::vector<AnisotoropicParticle> particles;
	const Particle originParticle = origin->toParticle(density);
	const Particle destParticle = dest->toParticle(density);
	const float start = origin->getRadius() + divideLength * 0.5f;
	const float end = length - dest->getRadius();// - divideLength * 0.5f;
	for (float l = start; l < end; l += divideLength) {
		const float ratio = l / length;
		const auto pos = getOriginJoint()->getPosition() * (1.0f - ratio) + getDestJoint()->getPosition() * (ratio);
		const Vector3d<float> radii(divideLength, thickness, thickness);
		const Ellipsoid<float> e(pos, radii);
		AnisotoropicParticle ap(e, density);
		particles.emplace_back(ap);
	}
	return particles;
}
