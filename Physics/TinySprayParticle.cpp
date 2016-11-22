#include "TinySprayParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TinySprayParticle::TinySprayParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	ITinyParticle(position, velocity, parent)
{
}

void TinySprayParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	this->velocity += dt * gravity;
}
