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
	const auto& fluidParticles = getFluidParticles();
	const auto& boundaryParticles = getBoundaryParticles();
	const auto& allParticles = getAllParticles();

	for (const auto& particle : allParticles) {
		particle->init();
	}

	NeighborFinder fluidFinder(effectLength, fluidParticles.size());
	for (const auto& particle : fluidParticles) {
		fluidFinder.add(particle);
	}
	fluidFinder.create(fluidParticles);
	fluidFinder.create(boundaryParticles);

	NeighborFinder boundaryFinder(effectLength, boundaryParticles.size());
	for (const auto& particle : boundaryParticles) {
		boundaryFinder.add(particle);
	}
	boundaryFinder.create(fluidParticles);

	auto pairs = fluidFinder.getPairs();
	const auto& bpairs = boundaryFinder.getPairs();

	pairs.insert(pairs.end(), bpairs.begin(), bpairs.end());
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		pairs[i].solveDensity();
	}

	for (int i = 0; i < static_cast<int>(allParticles.size()); ++i) {
		allParticles[i]->addSelfDensity();
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
		pairs[i].getParticle1()->solveSurfaceTension(*pairs[i].getParticle2());
		pairs[i].getParticle2()->solveSurfaceTension(*pairs[i].getParticle1());
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

