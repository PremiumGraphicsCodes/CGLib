#include "IISPHSolver.h"
#include "IISPHParticle.h"
#include "IISPHSpaceHash.h"

#include "IndexedFinder.h"
#include "../Core/SpaceHash.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

void IISPHSolver::simulate(const double dt, const double effectRadius)
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

	Vector3d<float> externalForce(0.0, -9.8f, 0.0f);
	for (auto p : particles) {
		p->predictAdvection1(externalForce, dt);
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