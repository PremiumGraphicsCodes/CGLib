#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Particle::Particle()
{}

Particle::Particle(const Vector3d<float>& center) :
	position(center)
{}

Particle::Particle(const Constant& constant, const Vector3d<float>& center) :
	constant(constant),
	position(center)
{
	density = constant.restDensity;
}

float Particle::getDensityRatio() const
{
	return density / constant.getRestDensity();
}

float Particle::getPressure() const
{
	return constant.pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float Particle::getMass() const
{
	return constant.getRestDensity() * std::pow(constant.getDiameter(), 3);
}

float Particle::getVolume() const
{
	return getMass() / density;
}

float Particle::getRestVolume() const
{
	return getMass() / getRestDensity();
}


void Particle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->position += this->velocity * timeStep;
}

void Particle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce;
}