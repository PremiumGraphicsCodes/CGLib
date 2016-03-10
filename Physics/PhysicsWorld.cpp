#include "PhysicsWorld.h"

#include "PhysicsParticleFindAlgo.h"
#include "BoundarySolver.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void ParticleWorld::simulate(const float effectLength, const float timeStep)
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
	const auto& pairs = algo.getPairs();

	/*
	NeighborFinder finder(effectLength, 1000);
	for (const auto& particle : particles) {
		finder.add(particle);
	}
	const auto& pairs = finder.getPairs();
	*/
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
		object->addExternalForce(externalForce);
	}

	BoundarySolver boundarySolver(timeStep, boundary);
	boundarySolver.solve(particles);

	for (const auto& object : objects) {
		object->addExternalForce(externalForce);
	}


	for (const auto& object : objects) {
		object->coordinate(timeStep);
	}

	for (const auto& object : objects) {
		object->forwardTime(timeStep);
	}
}

std::vector<SPHParticle*> ParticleWorld::getParticles()
{
	std::vector<SPHParticle*> ordered;
	for (const auto& object : objects) {
		const auto& particles = object->getParticles();
		ordered.insert(ordered.end(), particles.begin(), particles.end());
	}
	return ordered;
}


