#include "SPHParticle.h"

#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

SPHParticle::SPHParticle():
	restDensity(1.0f),
	constant(nullptr)
{
	density = restDensity;

}

SPHParticle::SPHParticle(const Particle& particle, SPHConstant* constant) :
	Particle(particle),
	constant(constant)
{}

SPHParticle::SPHParticle(const Vector3d<float>& center, float radius, float density, SPHConstant* constant) :
	Particle(center, density, radius),
	restDensity(density),
	constant(constant)
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
	return constant->getPressureCoe() * (std::pow(getDensityRatio(), 1) - 1.0f);
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
	this->force += externalForce * getDensity();
}

namespace {
	SPHKernel<float> kernel;
}


void SPHParticle::solveNormal(const SPHParticle& rhs)
{
	const auto& distanceVector = this->getPosition() - rhs.getPosition();
	this->normal += kernel.getPoly6KernelGradient(distanceVector, constant->getEffectLength()) * rhs.getVolume();
	//pairs[i].getParticle1()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
}

void SPHParticle::solveSurfaceTension(const SPHParticle& rhs)
{
	if (this->normal.getLengthSquared() < 0.1f) {
		return;
	}
	const auto distance = this->getPosition().getDistance( rhs.getPosition() );
	const auto n = this->normal.getNormalized();
	const float tensionCoe = (this->constant->getTensionCoe() + rhs.constant->getTensionCoe()) * 0.5f;;
	this->force -= tensionCoe * kernel.getPoly6KernelLaplacian(distance, constant->getEffectLength()) * n;
}


void SPHParticle::solvePressureForce(const SPHParticle& rhs)
{
	const auto pressure = (this->getPressure() + rhs.getPressure()) * 0.5f;
	const auto& distanceVector = (this->getPosition() - rhs.getPosition());
	const auto& f = kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength()) * pressure * rhs.getVolume();
	this->force += f;
}

void SPHParticle::solveViscosityForce(const SPHParticle& rhs)
{
	const auto viscosityCoe = (this->constant->getViscosityCoe() + rhs.constant->getViscosityCoe()) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = getPosition().getDistance(rhs.getPosition());
	this->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, constant->getEffectLength()) * rhs.getVolume());
}

void SPHParticle::addSelfDensity()
{
	this->addDensity(kernel.getPoly6Kernel(0.0, constant->getEffectLength()) * this->getMass());
}

void SPHParticle::addDensity(const SPHParticle& rhs)
{
	const float distance = this->getPosition().getDistance( rhs.getPosition() );
	this->addDensity(kernel.getPoly6Kernel(distance, constant->getEffectLength()) * rhs.getMass());
}