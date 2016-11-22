#include "TinyFoamParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TinyFoamParticle::TinyFoamParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	ITinyParticle(position, velocity, parent)
{
}

void TinyFoamParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	this->velocity = getAveragedLocalVelocity();
}
