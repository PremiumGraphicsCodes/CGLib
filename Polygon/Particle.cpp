#include "Particle.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Box<float> Particle::getBoundingBox() const
{
	const auto minx = position.getX() - radius;
	const auto miny = position.getY() - radius;
	const auto minz = position.getZ() - radius;
	const auto maxx = position.getX() + radius;
	const auto maxy = position.getY() + radius;
	const auto maxz = position.getZ() + radius;
	return Box<float>(Vector3d<float>(minx, miny, minz), Vector3d<float>(maxx, maxy, maxz));
}

Particle Particle::createBlended(const Particle& rhs, const float ratio) const
{
	assert(0.0f <= ratio && ratio <= 1.0f);
	auto p = this->position * (1.0f-ratio) - rhs.position * ( ratio);
	const auto d = this->density * (1.0f-ratio) + rhs.density * (ratio);
	const auto r = this->radius * (1.0f-ratio) + rhs.radius * (ratio);
	return Particle(p, d, r);
}


bool Particle::isCollided(const Particle& rhs)
{
	return position.getDistance(rhs.position) < (this->radius + rhs.radius);
}
