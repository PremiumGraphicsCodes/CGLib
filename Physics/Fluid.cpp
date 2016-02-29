#include "Fluid.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Fluid::Fluid()
{
}

void Fluid::addExternalForce(const Vector3d<float>& force)
{
	const auto particles = getParticles();
	for (const auto& particle : particles) {
		particle->addForce(force * particle->getDensity());
	}
}

void Fluid::forwardTime(const float timeStep)
{
	const auto particles = getParticles();
	for (const auto& particle : particles) {
		const auto& accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
		particle->addVelocity(accelaration * timeStep);
		particle->addCenter(particle->getVelocity() * timeStep);
	}
}