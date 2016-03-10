#include "ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

ParticlePair::ParticlePair() :
	particle1(nullptr),
	particle2(nullptr)
{}

ParticlePair::ParticlePair(SPHParticle* particle1, SPHParticle* particle2) :
	particle1(particle1),
	particle2(particle2)
{
}

Vector3d<float> ParticlePair::getDistanceVector() const
{
	return Math::Vector3d<float>(particle1->getPosition() - particle2->getPosition());
}

float ParticlePair::getDistance() const
{
	return getDistanceVector().getLength();
}

float ParticlePair::getDistanceSquared() const
{
	return particle1->getPosition().getDistanceSquared(particle2->getPosition());
}

float ParticlePair::getPressure() const
{
	return (particle1->getPressure() + particle2->getPressure()) * 0.5f;
}

float ParticlePair::getViscosityCoe() const
{
	return (particle1->getViscosityCoe() + particle2->getViscosityCoe()) * 0.5f;
}

Vector3d<float> ParticlePair::getVelocityDiff() const
{
	return Math::Vector3d<float>(particle1->getVelocity(), particle2->getVelocity());
}

bool ParticlePair::isValid() const
{
	return
		particle1 != nullptr &&
		particle2 != nullptr &&
		particle1 != particle2;
}
