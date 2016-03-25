#include "ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHParticlePair::SPHParticlePair() :
	particle1(nullptr),
	particle2(nullptr)
{}

SPHParticlePair::SPHParticlePair(SPHParticle* particle1, SPHParticle* particle2) :
	particle1(particle1),
	particle2(particle2)
{
}

Vector3d<float> SPHParticlePair::getDistanceVector() const
{
	return Math::Vector3d<float>(particle1->getPosition() - particle2->getPosition());
}

float SPHParticlePair::getDistance() const
{
	return getDistanceVector().getLength();
}

float SPHParticlePair::getDistanceSquared() const
{
	return particle1->getPosition().getDistanceSquared(particle2->getPosition());
}

float SPHParticlePair::getPressure() const
{
	return (particle1->getPressure() + particle2->getPressure()) * 0.5f;
}

Vector3d<float> SPHParticlePair::getVelocityDiff() const
{
	return Math::Vector3d<float>(particle1->getVelocity(), particle2->getVelocity());
}

bool SPHParticlePair::isValid() const
{
	return
		particle1 != nullptr &&
		particle2 != nullptr &&
		particle1 != particle2;
}

void SPHParticlePair::solveDensity()
{
	particle1->addDensity(*particle2);
	particle2->addDensity(*particle1);
}

void SPHParticlePair::solvePressureForce()
{
	particle1->solvePressureForce(*particle2);
	particle2->solvePressureForce(*particle1);
}

void SPHParticlePair::solveViscosityForce()
{
	particle1->solveViscosityForce(*particle2);
	particle2->solveViscosityForce(*particle1);
}