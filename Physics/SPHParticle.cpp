#include "SPHParticle.h"

#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

SPHParticle::SPHParticle():
	restDensity(1.0f)
{
	density = restDensity;

}

SPHParticle::SPHParticle(const Particle& particle, float pressureCoe, float viscosityCoe) :
	Particle(particle),
	pressureCoe(pressureCoe),
	viscosityCoe(viscosityCoe)
{}

SPHParticle::SPHParticle(const Vector3d<float>& center, float radius, float density, float pressureCoe, float viscosityCoe) :
	Particle(center, density, radius),
	pressureCoe(pressureCoe),
	viscosityCoe(viscosityCoe),
	restDensity(density)
{
	this->density = restDensity;
}

void SPHParticle::init()
{
	density = 0.0;
	normal = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
	force = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
}

float SPHParticle::getDensityRatio() const
{
	return density / restDensity;
}

float SPHParticle::getPressure() const
{
	return pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float SPHParticle::getMass() const
{
	return restDensity * std::pow(getDiameter(), 3);
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
namespace {
	SPHKernel<float> kernel;
}


void SPHParticle::addNormal(const SPHParticle& rhs, const float effectLength)
{
	const auto distanceVector = this->getPosition() - rhs.getPosition();
	this->normal += kernel.getPoly6KernelGradient(distanceVector, effectLength) * rhs.getVolume();
	//pairs[i].getParticle1()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
}

#include "SPHKernel.h"


void SPHParticle::solvePressureForce(const SPHParticle& rhs, const float effectLength)
{
	const auto pressure = (this->getPressure() + rhs.getPressure()) * 0.5f;
	const auto& distanceVector = (this->getPosition() - rhs.getPosition());
	const auto& f = kernel.getSpikyKernelGradient(distanceVector, effectLength) * pressure * rhs.getVolume();
	this->force += f;
}

void SPHParticle::solveViscosityForce(const SPHParticle& rhs, const float effectLength)
{
	const auto viscosityCoe = (this->viscosityCoe + rhs.viscosityCoe) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = getPosition().getDistance(rhs.getPosition());
	this->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * rhs.getVolume());
}

void SPHParticle::addSelfDensity(const float effectLength)
{
	this->addDensity(kernel.getPoly6Kernel(0.0, effectLength) * this->getMass());
}

void SPHParticle::addDensity(const SPHParticle& rhs, const float effectLength)
{
	const float distance = this->getPosition().getDistance( rhs.getPosition() );
	this->addDensity(kernel.getPoly6Kernel(distance, effectLength) * rhs.getMass());
}