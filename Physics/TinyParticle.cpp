#include "TinyParticle.h"
#include "BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

ITinyParticle::ITinyParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	position(position),
	velocity(velocity),
	parent(parent)
{
}

Vector3d<float> ITinyParticle::getAveragedLocalVelocity() const
{
	SPHKernel<float> kernel(parent->getEffectLength());
	const auto& neighbors = parent->getNeighbors();
	const auto effectLength = parent->getEffectLength();
	Vector3d<float> numerator;
	float denominator = 0.0f;
	for (auto n : neighbors) {
		const auto diff = this->position - n->getPosition();
		numerator += n->getVelocity() * kernel.getPoly6Kernel2(parent->getEffectLength());
		denominator += kernel.getPoly6Kernel2(parent->getEffectLength());
	}
	if (denominator == 0.0f) {
		return Vector3d<float>(0,0,0);
	}
	return numerator / denominator;
}


void ITinyParticle::integrate(const Vector3d<float>& externalForce, const float dt)
{
	const auto acc = externalForce / mass;
	velocity += dt * acc;
	position += dt * velocity;
}

TinySprayParticle::TinySprayParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	ITinyParticle(position, velocity, parent)
{
}

void TinySprayParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	this->velocity += dt * gravity;
}

TinyFoamParticle::TinyFoamParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent) :
	ITinyParticle(position, velocity, parent)
{
}

void TinyFoamParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	this->velocity = getAveragedLocalVelocity();
}

TinyBubbleParticle::TinyBubbleParticle(const Vector3d<float>& position, const Vector3d<float>& velocity, BubbleParticle* parent):
	ITinyParticle(position, velocity, parent)
{}

void TinyBubbleParticle::updateVelocity(const float dt, const Vector3d<float>& gravity)
{
	const auto kb = 0.01f;
	const auto kd = 0.1f;
	this->velocity += dt * (kb * gravity) + kd * (getAveragedLocalVelocity() - this->velocity) / dt;
}
