#include "PBSPHParticle.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

PBSPHParticle::PBSPHParticle(const int id) :
	constant(nullptr),
	Particle(id)
{
}

PBSPHParticle::PBSPHParticle(const Particle& particle, SPHConstant* constant) :
	Particle(particle),
	constant(constant)
{}

PBSPHParticle::PBSPHParticle(const Vector3d<float>& center, float radius, SPHConstant* constant, const int id) :
	Particle(center, constant->getDensity(), radius, id),
	constant(constant)
{
	this->density = constant->getDensity();
}

void PBSPHParticle::setNeighbors(const std::list<PBSPHParticle*>& neighbors)
{
	this->neighbors = neighbors;
	this->neighbors.remove(this);
}


void PBSPHParticle::init()
{
	density = 0.0;
	normal = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
	force = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
}

float PBSPHParticle::getDensityRatio() const
{
	return density / constant->getDensity();
}

float PBSPHParticle::getPressure() const
{
	return constant->getPressureCoe() * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float PBSPHParticle::getMass() const
{
	return constant->getDensity() * std::pow(getDiameter(), 3);
}

float PBSPHParticle::getVolume() const
{
	return getMass() / density;
}

float PBSPHParticle::getRestVolume() const
{
	return getMass() / constant->getDensity();
}

void PBSPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->move(this->velocity * timeStep);
}

void PBSPHParticle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce * getDensity();
}

namespace {
	SPHKernel<float> kernel;
}

void PBSPHParticle::solveNormal(const PBSPHParticle& rhs)
{
	const auto& distanceVector = this->getPosition() - rhs.getPosition();
	this->normal += kernel.getPoly6KernelGradient(distanceVector, constant->getEffectLength()) * rhs.getVolume();
	//pairs[i].getParticle1()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
}

void PBSPHParticle::solveSurfaceTension(const PBSPHParticle& rhs)
{
	if (this->normal.getLengthSquared() < 0.1f) {
		return;
	}
	const auto distance = this->getPosition().getDistance(rhs.getPosition());
	const auto n = this->normal.normalized();
	const float tensionCoe = (this->constant->getTensionCoe() + rhs.constant->getTensionCoe()) * 0.5f;;
	this->force -= tensionCoe * kernel.getPoly6KernelLaplacian(distance, constant->getEffectLength()) * n;
}

void PBSPHParticle::solvePressureForce(const PBSPHParticle& rhs)
{
	const auto pressure = (this->getPressure() + rhs.getPressure()) * 0.5f;
	const auto& distanceVector = (this->getPosition() - rhs.getPosition());
	const auto& f = kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength()) * pressure * rhs.getVolume();
	this->force += f;
}

void PBSPHParticle::solveViscosityForce(const PBSPHParticle& rhs)
{
	const auto viscosityCoe = (this->constant->getViscosityCoe() + rhs.constant->getViscosityCoe()) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = getPosition().getDistance(rhs.getPosition());
	this->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, constant->getEffectLength()) * rhs.getVolume());
}

void PBSPHParticle::addSelfDensity()
{
	this->addDensity(kernel.getPoly6Kernel(0.0, constant->getEffectLength()) * this->getMass());
}

void PBSPHParticle::addDensity(const PBSPHParticle& rhs)
{
	const float distance = this->getPosition().getDistance(rhs.getPosition());
	this->addDensity(kernel.getPoly6Kernel(distance, constant->getEffectLength()) * rhs.getMass());
}

void PBSPHParticle::predictPosition(const float dt)
{
	this->prevPosition = this->position;
	this->velocity += dt * this->force;
	this->position += dt * this->velocity;
}

void PBSPHParticle::solveConstrantGradient()
{
	this->constraintGrad = Vector3d<float>(0, 0, 0);
	for (auto n : neighbors) {
		this->constraintGrad += this->getConstraintGradient(*n);
	}
}


Vector3d<float> PBSPHParticle::getConstraintGradient(const PBSPHParticle& rhs)
{
	const auto& distanceVector = this->getPosition() - rhs.getPosition();
	return 1.0f / this->density * kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength());
}

void PBSPHParticle::solveDensityConstraint()
{
	this->densityConstraint = 0.0f;
	const auto c = this->getDensity() / this->constant->getDensity() - 1.0f;
	this->densityConstraint += this->constraintGrad.getLengthSquared();
}

void PBSPHParticle::solvePositionCorrection()
{
	this->positionCorrection = Vector3d<float>(0, 0, 0);
	for (auto n : neighbors) {
		this->positionCorrection += getPositionCorrection(*n);
	}
}


Vector3d<float> PBSPHParticle::getPositionCorrection(const PBSPHParticle& rhs)
{
	const auto& distanceVector = this->getPosition() - rhs.getPosition();
	return 1.0f / this->constant->getDensity() * (this->densityConstraint + rhs.densityConstraint) * kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength());
}

void PBSPHParticle::solveDensity()
{
	this->density = 0.0f;
	for (auto n : neighbors) {
		addDensity(*n);
	}
	addSelfDensity();
}

void PBSPHParticle::updatePredictPosition(const float dt)
{
	this->position = this->position + positionCorrection;
}

void PBSPHParticle::updateVelocity(const float dt)
{
	this->velocity = (this->position - this->prevPosition) / dt;
}

void PBSPHParticle::updatePosition()
{
	this->prevPosition = this->position;
}



