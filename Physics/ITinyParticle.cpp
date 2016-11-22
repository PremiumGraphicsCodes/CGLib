#include "ITinyParticle.h"
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
		const auto weight = kernel.getPoly6Kernel2(diff.getLengthSquared());
		numerator += n->getVelocity() * weight;
		denominator += weight;
	}
	if (denominator == 0.0f) {
		return Vector3d<float>(0,0,0);
	}
	return numerator / denominator;
}

void ITinyParticle::integrate(const Vector3d<float>& externalForce, const float dt)
{
	updateVelocity(dt, externalForce);
	position += dt * velocity;
}
