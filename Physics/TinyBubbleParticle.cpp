#include "TinyBubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TinyBubbleParticle::TinyBubbleParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	ITinyParticle(position, velocity, parent)
{}

void TinyBubbleParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	const auto kb = 0.01f;
	const auto kd = 0.1f;
	this->velocity += dt * (kb * gravity) + kd * (getAveragedLocalVelocity() - this->velocity) / dt;
}
