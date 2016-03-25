#ifndef __CRYSTAL_PHYSICS_INDEXED_PARTICLE_H__
#define __CRYSTAL_PHYSICS_INDEXED_PARTICLE_H__

#include "../Math/Vector3d.h"
#include "../Math/Index3d.h"
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

	static int toGridId(const Math::Vector3d<float> pos, const float effectLength);

	static Math::Index3d toIndex(const Math::Vector3d<float> pos, const float effectLength);

	int getGridID() const { return gridID; }

	bool operator<(const IndexedParticle& rhs) {
		return this->getGridID() < rhs.getGridID();
	}

	SPHParticle* getParticle() const { return particle; }

private:
	static int toIdX(Math::Index3d index);



private:
	SPHParticle* particle;
	int gridID;
};

	}
}

#endif