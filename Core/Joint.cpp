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

void Joint::scale(const Vector3d<float>& s)
{
	this->radii += s;
	if (radii.getX() < 0) {
		this->radii.setX(Tolerance<float>::getLooseTolerance());
	}
	if (radii.getY() < 0) {
		this->radii.setY(Tolerance<float>::getLooseTolerance());
	}
	if (radii.getZ() < 0) {
		this->radii.setZ(Tolerance<float>::getLooseTolerance());
	}

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

Box3d<float> Joint::getBoundingBox() const
{
	return toParticle(1000.0f).getBoundingBox();
}
