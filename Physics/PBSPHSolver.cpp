#include "PBSPHSolver.h"
#include "PBSPHParticle.h"
#include "IISPHSpaceHash.h"

#include "IndexedFinder.h"
#include "../Core/SpaceHash.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

void PBSPHSolver::simulate(const float dt, const float effectRadius)
{
	for (auto p : particles) {
		p->init();
	}


	Vector3d<float> externalForce(0.0, -9.8f, 0.0f);
	//Vector3d<float> externalForce(0.0f, 0.0f, 0.0f);
	for (auto p : particles) {
		p->addExternalForce(externalForce);
		p->predictPosition(dt);
	}

	const int tableSize = static_cast<int>(particles.size());
	IISPHSpaceHash<PBSPHParticle> space(effectRadius, tableSize);
	for (auto p : particles) {
		space.add(p);
	}

	for (auto p : particles) {
		const auto& neighbors = space.getNeighbor(p);
		p->setNeighbors(neighbors);
	}

	//for (auto p : particles) {
	//	p->integrate(dt);
	//}

}