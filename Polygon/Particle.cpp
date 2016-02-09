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

bool Particle::isCollided(const Particle& rhs)
{
	return position.getDistance(rhs.position) < (this->radius + rhs.radius);
}
