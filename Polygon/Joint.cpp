#include "Joint.h"

using namespace Crystal::Core;


Particle Joint::toParticle(const float density) const
{
	return Particle(position, density, radius);
}