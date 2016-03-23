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

	for (const auto& particle : allParticles) {
		particle->init();
	}

	NeighborFinder finder(effectLength, allParticles.size());
	for (const auto& particle : allParticles) {
		finder.add(particle);
	}

	finder.create(allParticles);

	const auto& pairs = finder.getPairs();
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].getParticle1()->addDensity(*pairs[i].getParticle2(), effectLength);
	}

	for (int i = 0; i < static_cast<int>(allParticles.size()); ++i) {
		allParticles[i]->addSelfDensity(effectLength);
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].getParticle1()->solvePressureForce(*pairs[i].getParticle2(), effectLength);
		pairs[i].getParticle1()->solveViscosityForce(*pairs[i].getParticle2(), effectLength);
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].getParticle1()->solveNormal(*pairs[i].getParticle2(), effectLength);
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].getParticle1()->solveSurfaceTension(*pairs[i].getParticle2(), effectLength);
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

