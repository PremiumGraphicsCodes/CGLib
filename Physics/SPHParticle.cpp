#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

SPHParticle::SPHParticle()
{}

SPHParticle::SPHParticle(const Vector3d<float>& center, float radius, float density) :
	Particle(center, radius, density)
{}

SPHParticle::SPHParticle(const Constant& constant, const Vector3d<float>& center) :
	constant(constant),
	Particle(center, constant.getRestDensity(), constant.getDiameter()*0.5f)
{
	density = constant.restDensity;
}

float SPHParticle::getDensityRatio() const
{
	return density / constant.getRestDensity();
}

float SPHParticle::getPressure() const
{
	return constant.pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float SPHParticle::getMass() const
{
	return constant.getRestDensity() * std::pow(constant.getDiameter(), 3);
}

float SPHParticle::getVolume() const
{
	return getMass() / density;
}

float SPHParticle::getRestVolume() const
{
	return getMass() / getRestDensity();
}


void SPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->move( this->velocity * timeStep );
}

void SPHParticle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce;
}