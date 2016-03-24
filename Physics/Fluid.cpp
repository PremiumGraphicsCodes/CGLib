#include "Fluid.h"

#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Fluid::Fluid()
{
}

Fluid::Fluid(const Box<float>& box, const float divideLength, const float restDensity, const SPHConstant& constant) :
	PhysicsObject(box, divideLength, restDensity, constant)
{
}


Fluid::Fluid(const std::vector<SPHParticle*>& particles) :
	PhysicsObject(particles)
{
}


void Fluid::addExternalForce(const Vector3d<float>& force)
{
	const auto particles = getParticles();
	for (const auto& particle : particles) {
		particle->addForce(force * particle->getDensity());
	}
}

/*
void Fluid::forwardTime(const float timeStep)
{
	const auto particles = getParticles();
	for (const auto& particle : particles) {
		const auto& accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
		particle->addVelocity(accelaration * timeStep);
		particle->addCenter(particle->getVelocity() * timeStep);
	}
}
*/