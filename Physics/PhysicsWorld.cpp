#include "PhysicsWorld.h"

#include "PhysicsParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void PhysicsWorld::simulate()
{
	const auto& particles = getParticles();

	if (particles.empty()) {
		return;
	}

	for (const auto& particle : particles) {
		particle->init();
	}

	ParticleFindAlgo<float> algo;
	algo.createPairs(particles, effectLength);
	const ParticlePairVector& pairs = algo.getPairs();

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		const float distance = pairs[i].getDistance();
		pairs[i].getParticle1()->addDensity(kernel.getPoly6Kernel(distance, effectLength) * pairs[i].getParticle2()->getMass());
	}

	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		particles[i]->addDensity(kernel.getPoly6Kernel(0.0, effectLength) * particles[i]->getMass());
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		const auto pressure = pairs[i].getPressure();
		const auto& distanceVector = pairs[i].getDistanceVector();
		pairs[i].getParticle1()->addForce(kernel.getSpikyKernelGradient(distanceVector, effectLength) * pressure * pairs[i].getParticle2()->getVolume());

		const auto viscosityCoe = pairs[i].getViscosityCoe();
		const auto& velocityDiff = pairs[i].getVelocityDiff();
		const auto distance = pairs[i].getDistance();
		pairs[i].getParticle2()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
	}

	for (const auto& object : objects) {
		object->coordinate();
	}

}

std::vector<Particle*> PhysicsWorld::getParticles()
{
	std::vector<Particle*> ordered;
	for (const auto& object : objects) {
		const auto& particles = object->getParticles();
		ordered.insert(ordered.end(), particles.begin(), particles.end());
	}
	return ordered;
}


void PhysicsWorld::solveBoundary(const std::vector<Particle*>& particles) {
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		particles[i]->addForce(getBoundaryForce(particles[i]->getCenter()) * particles[i]->getDensity());
	}
}

Vector3d<float> PhysicsWorld::getBoundaryForce(const Vector3d<float>& center)
{
	Math::Vector3d<float> force = Math::Vector3d<float>::Zero();

	force += getForceX(center.getX());
	force += getForceY(center.getY());
	force += getForceZ(center.getZ());

	return force;
}

Vector3d<float> PhysicsWorld::getForceX(const float x)
{
	float over = 0;
	if (x > boundary.getMaxX()) {
		over = x - boundary.getMaxX();
	}
	else if (x < boundary.getMinX()) {
		over = x - boundary.getMinX();
	}

	const auto force = getForce(over);
	return Math::Vector3d<float>::UnitX() * force;
}

Vector3d<float> PhysicsWorld::getForceY(const float y)
{
	float over = 0;
	if (y > boundary.getMaxY()) {
		over = y - boundary.getMaxY();
	}
	else if (y < boundary.getMinY()) {
		over = y - boundary.getMinY();
	}
	const auto force = getForce(over);
	return Math::Vector3d<float>::UnitY() * force;
}

Vector3d<float> PhysicsWorld::getForceZ(const float z)
{
	float over = 0;
	if (z > boundary.getMaxZ()) {
		over = z - boundary.getMaxZ();
	}
	else if (z < boundary.getMinZ()) {
		over = z - boundary.getMinZ();
	}
	const float force = getForce(over);
	return Math::Vector3d<float>::UnitZ() * force;
}

float PhysicsWorld::getForce(const float over) {
	return -over / timeStep / timeStep;
}
