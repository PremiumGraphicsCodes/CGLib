#include "IISPHSolver.h"
#include "IISPHParticle.h"
#include "IISPHSpaceHash.h"
#include "IISPHBoundarySolver.h"

#include "IndexedFinder.h"
#include "../Core/SpaceHash.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

void IISPHSolver::simulate(const float dt, const float effectRadius)
{
	const int tableSize = static_cast<int>(particles.size());
	IISPHSpaceHash<IISPHParticle> space(effectRadius, tableSize);
	for (auto p : particles) {
		space.add(p);
	}

	for (auto p : particles) {
		const auto& neighbors = space.getNeighbor(p);
		p->setNeighbors(neighbors);
	}

	for (auto p : particles) {
		p->init();
	}


	IISPHBoundarySolver boundarySolver(dt, Box3d<float>(Vector3d<float>(-10.0, 0.0, -10.0), Vector3d<float>(10.0, 10.0, 10.0)));
	boundarySolver.solve(particles);

	Vector3d<float> externalForce(0.0, -9.8f, 0.0f);
	//Vector3d<float> externalForce(0.0f, 0.0f, 0.0f);
	for (auto p : particles) {
		p->addExternalForce(externalForce);
	}
	for (auto p : particles) {
		p->predictAdvection1(dt);
	}
	for (auto p : particles) {
		p->predictAdvection2(dt);
	}

	int i = 0;
	const float relaxation = 0.5f;
	while (i < 2) {
		for (auto p : particles) {
			p->solveDijPj(dt);
		}
		for (auto p : particles) {
			p->solvePressure(dt);
		}
		++i;
	}
	for (auto p : particles) {
		p->integrate(dt);
	}

}