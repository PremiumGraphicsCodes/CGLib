#include "IISPHParticle.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

IISPHParticle::IISPHParticle(const int id) :
	constant(nullptr),
	Particle(id),
	pressure(0.0f)
{
}

IISPHParticle::IISPHParticle(const Particle& particle, SPHConstant* constant) :
	Particle(particle),
	constant(constant),
	pressure(0.0f)
{}

IISPHParticle::IISPHParticle(const Vector3d<float>& center, float radius, SPHConstant* constant, const int id) :
	Particle(center, constant->getDensity(), radius, id),
	constant(constant),
	pressure(0.0f)
{
	this->density = constant->getDensity();
}

void IISPHParticle::setNeighbors(const std::list<IISPHParticle*>& neighbors)
{
	this->neighbors = neighbors;
	//this->neighbors.remove(this);
}

void IISPHParticle::init()
{
	density = 0.0;
	normal = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
	force = Math::Vector3d<float>(0.0f, 0.0f, 0.0f);
	advVelocity = Vector3d<float>(0.0f, 0.0f, 0.0f);
	aii = 0.0f;
	dii = Vector3d<float>(0.0f, 0.0f, 0.0f);
	dijp = Vector3d<float>(0.0f, 0.0f, 0.0f);
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

void IISPHParticle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce * getMass();
}

namespace {
	SPHKernel<float> kernel;
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
	this->addDensity(kernel.getCubicSpline(0.0, constant->getEffectLength()) * this->getMass());
}

void IISPHParticle::addDensity(const IISPHParticle& rhs)
{
	const float distance = this->getPosition().getDistance(rhs.getPosition());
	this->addDensity(kernel.getCubicSpline(distance, constant->getEffectLength()) * rhs.getMass());
}

void IISPHParticle::predictAdvection1(const float dt)
{
	solveDensity();
	this->advVelocity = this->velocity + dt * force / getMass();
	for (auto n : neighbors) {
		this->dii += getDii(n, dt);
	}
}

void IISPHParticle::predictAdvection2(const float dt)
{
	advDensity = density;
	for (auto n : neighbors) {
		const auto kernelGrad = kernel.getCubicSplineGradient(getDiff(n), constant->getEffectLength());
		advDensity += dt * n->getMass() * (this->advVelocity - n->advVelocity).getInnerProduct(kernelGrad);
	}
	//this->density /= advDensity;
	prevPressure = 0.5f * pressure;
	this->pressure = prevPressure;
	this->aii = 0.0f;
	for (auto n : neighbors) {
		const auto kernelGrad = kernel.getCubicSplineGradient(getDiff(n), constant->getEffectLength());
		const auto& dii = getDii(n, dt);
		const auto& dji = n->getDij(this, dt);
		aii += n->getMass() * (dii - dji).getInnerProduct(kernelGrad);
	}
}

void IISPHParticle::solveDijPj(const float dt)
{
	for (auto n : neighbors) {
		this->dijp += getDij(n, dt) * n->pressure;
	}
}

void IISPHParticle::solvePressure(const float dt)
{
	const float relaxation = 0.5f;
	float p = 0.0f;
	for (auto n : neighbors) {
		const auto& kernelGrad = kernel.getCubicSplineGradient(getDiff(n), constant->getEffectLength());
		const auto invDensity = 1.0f / n->density;
		const float fac = dt * dt * n->getMass() * invDensity * invDensity * n->density;
		const auto djkpk = n->dijp - fac * kernelGrad;
		p += (this->dijp - (n->dii * n->pressure) - djkpk).getInnerProduct(kernelGrad);
	}
	float totalMass = 0.0f;
	for (auto n : neighbors) {
		totalMass += n->getMass();
	}
	p *= totalMass;
	const auto pp = constant->getDensity() - this->advDensity - p;
	if (Tolerance<float>::isEqualStrictly(aii)) {
		;//this->pressure = nextPressure;
	}
	else {
		this->pressure = (1.0f - relaxation) * prevPressure + relaxation / aii * pp;
		this->prevPressure = this->pressure;
	}
}


void IISPHParticle::integrate(const float dt)
{
	Vector3d<float> pressureForce;
	/*
	for (auto n : neighbors) {
		const auto diff = this->getPosition() - n->getPosition();
		const auto& kernelGrad = kernel.getCubicSplineGradient(diff, constant->getEffectLength());
		pressureForce += this->getMass() * n->getMass()  * (this->pressure / this->density / this->density + n->pressure / n->density / n->density) * kernelGrad;
	}
	*/
	pressureForce = dii * pressure;
	pressureForce += dijp;

	//pressureForce = pressureForce / dt / dt;
	//pressureForce = pressureForce * getMass();

	const auto mass = getMass();
	this->velocity = this->advVelocity + dt * pressureForce / getMass();// / getMass();
	this->position = this->position + dt * this->velocity;
}

void IISPHParticle::solveDensity()
{
	for (auto n : neighbors) {
		addDensity(*n);
	}
	//addSelfDensity();
}

Vector3d<float> IISPHParticle::getDii(IISPHParticle* rhs, const float dt) const
{
	const auto& kernelGrad = kernel.getCubicSplineGradient(getDiff(rhs), constant->getEffectLength());
	return -dt * dt * rhs->getMass() / (this->getDensity() * this->getDensity()) * kernelGrad;
}


Vector3d<float> IISPHParticle::getDij(IISPHParticle* rhs, const float dt) const
{
	const auto& kernelGrad = kernel.getCubicSplineGradient(getDiff(rhs), constant->getEffectLength());
	return -dt * dt * rhs->getMass() / (rhs->getDensity() * rhs->getDensity()) * kernelGrad;
}

Vector3d<float> IISPHParticle::getDiff(const IISPHParticle* rhs) const
{
	return rhs->getPosition() - this->getPosition();
}
