#include "stdafx.h"
#include "Joint.h"

#include "../Math/Quaternion.h"
#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Joint* Joint::clone(const unsigned int newId) const
{
	return new Joint(position, radii, newId);
}


AnisotoropicParticle Joint::toParticle(const float density) const
{
	const Ellipsoid<float> e(position, radii, getOrientation());
	return AnisotoropicParticle(e, density);
}

Ellipsoid<float> Joint::toEllipsoid() const
{
	return Ellipsoid<float>(position, radii, getOrientation());
}
