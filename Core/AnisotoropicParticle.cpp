#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

AnisotoropicParticle::AnisotoropicParticle(const int id)
	: IParticle(id)
{}

AnisotoropicParticle::AnisotoropicParticle(const Ellipsoid<float>& ellipsoid, const float density, const int id) :
	IParticle(ellipsoid.getCenter(),density, id),
	scale(ellipsoid.getRadii()),
	orientation(Quaternion<float>::Unit())
{
}

Matrix3d<float> AnisotoropicParticle::getMatrix() const
{
	return Matrix3d<float>();
}
