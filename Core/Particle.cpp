#include "Particle.h"
#include "AnisotoropicParticle.h"

#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Particle::Particle(const int id) :
	IParticle(id)
{}

Particle::Particle(const Vector3d<float>& position, const float density, const float radius, const int id) :
	IParticle(position, density, id),
	radius(radius)
{}

Box3d<float> Particle::getBoundingBox() const
{
	const auto minx = position.getX() - radius;
	const auto miny = position.getY() - radius;
	const auto minz = position.getZ() - radius;
	const auto maxx = position.getX() + radius;
	const auto maxy = position.getY() + radius;
	const auto maxz = position.getZ() + radius;
	return Box3d<float>(Vector3d<float>(minx, miny, minz), Vector3d<float>(maxx, maxy, maxz));
}

Particle Particle::createBlended(const Particle& rhs, const float ratio) const
{
	assert(0.0f <= ratio && ratio <= 1.0f);
	auto p = this->position * (1.0f-ratio) + rhs.position * ( ratio);
	const auto d = this->density * (1.0f-ratio) + rhs.density * (ratio);
	const auto r = this->radius * (1.0f-ratio) + rhs.radius * (ratio);
	return Particle(p, d, r);
}


bool Particle::isCollided(const Particle& rhs)
{
	return position.getDistance(rhs.position) < (this->radius + rhs.radius);
}

#include "../Math/Tolerance.h"

bool Particle::equals(const Particle& rhs) const
{
	return (this->position == rhs.position) &&
		Tolerance<float>::isEqualLoosely(this->density, rhs.density) &&
		Tolerance<float>::isEqualLoosely(this->radius, rhs.radius);
}

bool Particle::operator==(const Particle& rhs) const
{
	return equals(rhs);
}

bool Particle::operator!=(const Particle& rhs) const
{
	return !equals(rhs);
}

AnisotoropicParticle Particle::toAnisotoropic(const int newId) const
{
	Ellipsoid<float> e(getPosition(),radius);
	return AnisotoropicParticle(e, density, newId);
}

Matrix3d<float> Particle::getMatrix() const
{
	return Matrix3d<float>(radius, 0, 0,
		0, radius, 0,
		0, 0, radius);
}