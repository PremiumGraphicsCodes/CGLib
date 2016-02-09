#include "Joint.h"

using namespace Crystal::Polygon;


Particle Joint::toParticle() const
{
	return Particle(position, density, radius);
}