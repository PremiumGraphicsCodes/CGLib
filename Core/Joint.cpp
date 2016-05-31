#include "Joint.h"

using namespace Crystal::Core;

Joint* Joint::clone(const unsigned int newId) const
{
	return new Joint(position, radius, newId);
}


Particle Joint::toParticle(const float density) const
{
	return Particle(position, density, radius);
}