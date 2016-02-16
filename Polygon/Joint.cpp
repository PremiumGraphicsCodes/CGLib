#include "Joint.h"

using namespace Crystal::Polygon;


Particle Joint::toParticle(const float density, const float radius) const
{
	return Particle(position, density, radius);
}