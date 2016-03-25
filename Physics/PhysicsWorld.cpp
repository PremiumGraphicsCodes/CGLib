#include "PhysicsWorld.h"

#include "BoundarySolver.h"
#include "NeighborFinder.h"

#include "BulletRigid.h"
#include "IndexedFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void ParticleWorld::add(BulletRigid* rigid)
{
	bulletRigids.push_back(rigid);
}

void ParticleWorld::simulate(const float effectLength, const float timeStep)
{
	const auto& fluidParticles = getFluidParticles();
	const auto& boundaryParticles = getBoundaryParticles();
	const auto& allParticles = getAllParticles();

	for (const auto& particle : allParticles) {
		particle->init();
	}

	NeighborFinder boundaryFinder(effectLength, boundaryParticles.size());
	for (auto p : boundaryParticles) {
		boundaryFinder.add(p);
	}
	boundaryFinder.create(fluidParticles);
	auto bpairs = boundaryFinder.getPairs();

	IndexedFinder algo(effectLength);
	algo.add(fluidParticles);
	algo.createPairs(fluidParticles);
	auto& pairs = algo.getPairs();

	pairs.insert(pairs.end(), bpairs.begin(), bpairs.end());

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].solveDensity();
	}

	for (int i = 0; i < static_cast<int>(fluidParticles.size()); ++i) {
		fluidParticles[i]->addSelfDensity();
	}

	for (int i = 0; i < static_cast<int>(boundaryParticles.size()); ++i) {
		boundaryParticles[i]->setDefaultDensity();// addSelfDensity();
	}


#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].solvePressureForce();
		pairs[i].solveViscosityForce();
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].getParticle1()->solveNormal(*pairs[i].getParticle2());
		pairs[i].getParticle2()->solveNormal(*pairs[i].getParticle1());

	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].solveSurfaceTension();
	}

	for (const auto& object : objects) {
		object->addExternalForce(externalForce);
	}

	BoundarySolver boundarySolver(timeStep, boundary);
	boundarySolver.solve(fluidParticles);

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

std::vector<SPHParticle*> ParticleWorld::getFluidParticles() const
{
	std::vector<SPHParticle*> results;
	for (const auto& object : objects) {
		const auto& particles = object->getParticles();
		results.insert(results.end(), particles.begin(), particles.end());
	}
	return results;
}

std::vector< SPHParticle*> ParticleWorld::getBoundaryParticles() const
{
	std::vector<SPHParticle*> results;
	for (const auto rigid : bulletRigids) {
		const auto& surfaces = rigid->getSurfaceParticles();
		results.insert(results.end(), surfaces.begin(), surfaces.end());
	}
	return results;
}



std::vector< SPHParticle*> ParticleWorld::getAllParticles() const
{
	std::vector<SPHParticle*> fluids = getFluidParticles();
	std::vector<SPHParticle*> boundaries = getBoundaryParticles();

	fluids.insert(fluids.end(), boundaries.begin(), boundaries.end());
	return fluids;
}

