#ifndef __CRYSTAL_PHYSICS_INDEXED_PARTICLE_H__
#define __CRYSTAL_PHYSICS_INDEXED_PARTICLE_H__

#include "../Math/Vector3d.h"
#include "SPHParticle.h"

namespace Crystal {
	namespace Physics {

class IndexedParticle
{
public:
	IndexedParticle() :
		particle(nullptr)
	{}

	IndexedParticle(SPHParticle* particle) :
		particle(particle)
	{
	}

public:
	void setGridID(const float effectLength);

	Math::Vector3d<float> getPosition() const { return particle->getPosition(); }

	int getGridID() const { return gridID; }

	static bool compare(const IndexedParticle& lhs, const IndexedParticle& rhs) {
		return lhs.getGridID() < rhs.getGridID();
	}

	SPHParticle* getParticle() const { return particle; }

private:
	int getID(int idX, int idY, int idZ) const {
		return (idZ << 20) + (idY << 10) + idX;
	}


private:
	SPHParticle* particle;
	int gridID;
};

	}
}

#endif