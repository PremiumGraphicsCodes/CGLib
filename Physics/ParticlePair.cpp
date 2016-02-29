#include "ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

ParticlePair::ParticlePair() :
	particle1(nullptr),
	particle2(nullptr)
{}

ParticlePair::ParticlePair(Particle* particle1, Particle* particle2) :
	particle1(particle1),
	particle2(particle2)
{
}

Vector3d<float> ParticlePair::getDistanceVector() const
{
	return Math::Vector3d<float>(particle1->getCenter() - particle2->getCenter());
}

float ParticlePair::getDistance() const
{
	return getDistanceVector().getLength();
}
