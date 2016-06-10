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

std::pair< Ellipsoid<float>, Quaternion<float> > Joint::toEllipsoid() const
{
	Ellipsoid<float> e(position, Vector3d<float>(radius, radius, radius));
	Quaternion<float> q;
	return std::make_pair(e, q);
}
