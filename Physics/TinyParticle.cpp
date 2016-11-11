#include "TinyParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

ITinyParticle::ITinyParticle(const Vector3d<float>& position, const Vector3d<float>& velocity) :
	position(position),
	velocity(velocity)
{
}

void ITinyParticle::integrate(const Vector3d<float>& externalForce, const float dt)
{
	const auto acc = externalForce / mass;
	velocity += dt * acc;
	position += dt * velocity;
}

TinySprayParticle::TinySprayParticle(const Vector3d<float>& position, const Vector3d<float>& velocity) :
	ITinyParticle(position, velocity)
{
}

TinyFoamParticle::TinyFoamParticle(const Vector3d<float>& position, const Vector3d<float>& velocity) :
	ITinyParticle(position, velocity)
{
}

TinyBubbleParticle::TinyBubbleParticle(const Vector3d<float>& position, const Vector3d<float>& velocity):
	ITinyParticle(position, velocity)
{}