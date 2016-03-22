#include "PhysicsWorld.h"

#include "BoundarySolver.h"
#include "NeighborFinder.h"

#include "BulletRigid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void ParticleWorld::add(BulletRigid* rigid)
{
	bulletRigids.push_back(rigid);
}

void ParticleWorld::simulate(const float effectLength, const float timeStep)
{
	const auto& particles = getParticles();
	const auto& allParticles = getAllParticles();

	/*
	if (particles.empty()) {
		return;
	}
	*/

	for (const auto& particle : allParticles) {
		particle->init();
	}



	/*
	ParticleFindAlgo<float> algo;
	algo.createPairs(particles, effectLength);
	const auto& pairs = algo.getPairs();
	*/

	NeighborFinder finder(effectLength, allParticles.size());
	for (const auto& particle : allParticles) {
		finder.add(particle);
	}


	/*
	for (const auto& particle : particles) {
		finder.create(particle);
	}
	*/
	finder.create(allParticles);

	const auto& pairs = finder.getPairs();
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		const float distance = pairs[i].getDistance();
		pairs[i].getParticle1()->addDensity(kernel.getPoly6Kernel(distance, effectLength) * pairs[i].getParticle2()->getMass());
	}

	for (int i = 0; i < static_cast<int>(allParticles.size()); ++i) {
		allParticles[i]->addDensity(kernel.getPoly6Kernel(0.0, effectLength) * allParticles[i]->getMass());
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		const auto pressure = pairs[i].getPressure();
		const auto& distanceVector = pairs[i].getDistanceVector();
		const auto& force = kernel.getSpikyKernelGradient(distanceVector, effectLength) * pressure * pairs[i].getParticle2()->getVolume();
		pairs[i].getParticle1()->addForce(force);
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		const auto viscosityCoe = pairs[i].getViscosityCoe();
		const auto& velocityDiff = pairs[i].getVelocityDiff();
		const auto distance = pairs[i].getDistance();
		pairs[i].getParticle1()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
	}

	/*
	for (const auto rigid : bulletRigids) {
		for (const auto& p : rigid->getSurfaceParticles()) {
			p->setForce( p->getForce() * p->getDensity());
		}
	}
	*/

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

std::vector<SPHParticle*> ParticleWorld::getParticles() const
{
	std::vector<SPHParticle*> results;
	for (const auto& object : objects) {
		const auto& particles = object->getParticles();
		results.insert(results.end(), particles.begin(), particles.end());
	}
	return results;
}

std::vector< SPHParticle*> ParticleWorld::getAllParticles() const
{
	std::vector<SPHParticle*> results = getParticles();

	for (const auto rigid : bulletRigids) {
		const auto& surfaces = rigid->getSurfaceParticles();
		results.insert(results.end(), surfaces.begin(), surfaces.end());
	}
	return results;
}

