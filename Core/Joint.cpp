#include "Joint.h"

#include "../Math/Quaternion.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Joint* Joint::clone(const unsigned int newId) const
{
	return new Joint(position, radius, newId);
}


Particle Joint::toParticle(const float density) const
{
	return Particle(position, density, radius);
}

Ellipsoid<float> Joint::toEllipsoid() const
{
	return Ellipsoid<float>(position, Vector3d<float>(radius, radius, radius));
}
