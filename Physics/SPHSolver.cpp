#include "SPHSolver.h"

#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

	SPHKernel<float> kernel;

void SPHSolver<float>::solve(const std::vector< PhysicsObject<float> >& objects, const float effectLength) {
	const auto& particles = getParticles(objects);

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
		object.coordinate();
	}

}
