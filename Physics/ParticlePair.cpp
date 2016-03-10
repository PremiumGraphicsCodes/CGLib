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

float SPHParticlePair::getViscosityCoe() const
{
	return (particle1->getViscosityCoe() + particle2->getViscosityCoe()) * 0.5f;
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
