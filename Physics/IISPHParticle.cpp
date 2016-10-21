#include "IISPHParticle.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

IISPHParticle::IISPHParticle(const int id) :
	constant(nullptr),
	Particle(id)
{
}

IISPHParticle::IISPHParticle(const Particle& particle, SPHConstant* constant) :
	Particle(particle),
	constant(constant)
{}

IISPHParticle::IISPHParticle(const Vector3d<float>& center, float radius, SPHConstant* constant, const int id) :
	Particle(center, constant->getDensity(), radius, id),
	constant(constant)
{
	this->density = constant->getDensity();
}

void IISPHParticle::setNeighbors(const std::list<IISPHParticle*>& neighbors)
{
	this->neighbors = neighbors;
}

void IISPHParticle::init()
{
	density = 0.0;
	normal = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
	force = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
}

float IISPHParticle::getDensityRatio() const
{
	return density / constant->getDensity();
}

float IISPHParticle::getPressure() const
{
	return constant->getPressureCoe() * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float IISPHParticle::getMass() const
{
	return constant->getDensity() * std::pow(getDiameter(), 3);
}

float IISPHParticle::getVolume() const
{
	return getMass() / density;
}

float IISPHParticle::getRestVolume() const
{
	return getMass() / constant->getDensity();
}

void IISPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->move(this->velocity * timeStep);
}

void IISPHParticle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce * getDensity();
}

namespace {
	SPHKernel<float> kernel;
}

void IISPHParticle::solvePressureForce(const IISPHParticle& rhs)
{
	const auto pressure = (this->getPressure() + rhs.getPressure()) * 0.5f;
	const auto& distanceVector = (this->getPosition() - rhs.getPosition());
	const auto& f = kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength()) * pressure * rhs.getVolume();
	this->force += f;
}

void IISPHParticle::solveViscosityForce(const IISPHParticle& rhs)
{
	const auto viscosityCoe = (this->constant->getViscosityCoe() + rhs.constant->getViscosityCoe()) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = getPosition().getDistance(rhs.getPosition());
	this->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, constant->getEffectLength()) * rhs.getVolume());
}

void IISPHParticle::addSelfDensity()
{
	this->addDensity(kernel.getPoly6Kernel(0.0, constant->getEffectLength()) * this->getMass());
}

void IISPHParticle::addDensity(const IISPHParticle& rhs)
{
	const float distance = this->getPosition().getDistance(rhs.getPosition());
	this->addDensity(kernel.getPoly6Kernel(distance, constant->getEffectLength()) * rhs.getMass());
}

void IISPHParticle::predictAdvection(const Vector3d<float>& externalForce, const float dt)
{
	solveDensity();
	predictVelocity(externalForce, dt);
	solveDisplace(dt);
}

void IISPHParticle::solvePressure(const float dt)
{
	int i = 0;
	while ((advDensity - constant->getDensity() > 0.01) || i < 2) {
		Vector3d<float> dp;
		for (auto n : neighbors) {
			const auto diff = this->getPosition() - n->getPosition();
			dp += dt * dt * -n->getMass() / n->getDensity() / n->getDensity() * n->getPressure() * kernel.getPoly6KernelGradient(diff, constant->getEffectLength());
		}
	}
}

void IISPHParticle::integrate(const float dt)
{
	this->velocity = this->advVelocity + dt * this->force / this->getMass();
	this->position = this->position + dt * this->velocity;
}

void IISPHParticle::solveDensity()
{
	for (auto n : neighbors) {
		addDensity(*n);
	}
	addSelfDensity();
}

void IISPHParticle::predictVelocity(const Vector3d<float>& externalForce, const float dt)
{
	this->advVelocity = this->velocity + dt * externalForce / getMass();
}

void IISPHParticle::solveDisplace(const float dt)
{
	for (auto n : neighbors) {
		const auto& diff = n->getPosition() - this->getPosition();
		const auto disp = -(n->getMass() / n->getDensity()) * kernel.getPoly6KernelGradient(diff, constant->getEffectLength());
		this->dispacement += (dt * dt * disp);
	}
}
