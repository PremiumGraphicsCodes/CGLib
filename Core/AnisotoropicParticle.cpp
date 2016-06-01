#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

AnisotoropicParticle::AnisotoropicParticle(const int id)
	: Particle(id)
{}

/*
AnisotoropicParticle::AnisotoropicParticle(const Ellipsoid<float>& ellipsoid, const int id) :
	Particle(ellipsoid.getPosition(),)
{

}
*/

Matrix3d<float> AnisotoropicParticle::getMatrix() const
{
	return Matrix3d<float>();
}
