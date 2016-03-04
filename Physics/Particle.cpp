#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void Particle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->center += this->velocity * timeStep;
}

void Particle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce;
}