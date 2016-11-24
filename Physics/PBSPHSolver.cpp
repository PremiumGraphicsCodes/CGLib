#include "PBSPHSolver.h"
#include "PBSPHParticle.h"
#include "IISPHSpaceHash.h"

#include "IndexedFinder.h"
#include "../Core/SpaceHash.h"
#include "../Math/Vector3d.h"
#include "PBSPHBoundarySolver.h"
#include "PBSPHObject.h"

#include "PBSPHNeighborFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

void PBSPHSolver::add(const PBSPHObject& object)
{
	for (auto p : object.getParticles()) {
		particles.push_back(p);
	}
}


void PBSPHSolver::simulate(const float dt, const float effectRadius, const float searchRadius, const int maxIter)
{
	for (auto p : particles) {
		p->init();
	}

	//Box3d<float> box(Vector3d<float>(-10, 0, -10), Vector3d<float>(10, 10, 10));
	PBSPHBoundarySolver boundarySolver(boundary);
	boundarySolver.solveForce(particles, dt);

	for (auto p : particles) {
		p->addExternalForce(externalForce);
		p->predictPosition(dt);
	}

	/*
	const int tableSize = static_cast<int>(particles.size());
	IISPHSpaceHash<PBSPHParticle> space(effectRadius, tableSize);
	for (auto p : particles) {
		space.add(p);
	}
	*/
	PBSPHNeighborFinder finder(searchRadius);
	finder.add(particles);
	finder.createPairs(particles);
	const auto& pairs = finder.getPairs();
	for (auto p : pairs) {
		auto p1 = p.getParticle1();
		auto p2 = p.getParticle2();
		p1->addNeighbor(p2);
		p2->addNeighbor(p1);
	}

	/*
	//for (auto p : particles) {
#pragma omp parallel for
	for(int i = 0; i < particles.size(); ++i) {
		const auto p = particles[i];
		const auto& neighbors = space.getNeighbor(p);
		p->setNeighbors(neighbors);
	}
	*/
	SPHKernel<float> kernel(effectRadius);
	for (auto p : particles) {
		p->setKernel(&kernel);
	}

	for (int iter = 0; iter < maxIter; ++iter) {
		#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->solveDensity();
		}
		//boundarySolver.solveDensity(particles);
#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->solveConstrantGradient();
		}
		//boundarySolver.solveConstraintGradient(particles);
#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->solveDensityConstraint();
		}

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->solvePositionCorrection();
		}
		//boundarySolver.solveCorrectPosition(particles);
#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->updatePredictPosition(dt);
		}
	}

	for (auto p : pairs) {
		p.solveNormal();
	}

	for (auto p : particles) {
		p->updateVelocity(dt);
		p->solveViscosity();
		//boundarySolver.solveViscosity(particles);
		p->updateViscosity();
		p->updatePosition();
	//	p->integrate(dt);
	}

}