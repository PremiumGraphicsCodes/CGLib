#include "IISPHSolver.h"
#include "IISPHParticle.h"

#include "IndexedFinder.h"
#include "../Core/SpaceHash.h"

//using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

void IISPHSolver::simulate(const double dt, const double effectRadius)
{
	const int tableSize = static_cast<int>(particles.size());
	SpaceHash<IISPHParticle> space(effectRadius, tableSize);
	for (auto p : particles) {
		space.add(p);
	}

	for (auto p : particles) {
		const auto& neighbors = space.getNeighbor(p);
		p->setNeighbors(neighbors);
	}

	for (auto p : particles) {

	}
}