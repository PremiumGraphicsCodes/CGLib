#ifndef __CRYSTAL_PHYSICS_SURFACE_BUILDER_H__
#define __CRYSTAL_PHYSICS_SURAFCE_BUILDER_H__

#include "SPHParticle.h"

namespace Crystal {
	namespace Physics {

class AnisotropicParticle : public Polygon::Particle
{
public:
	AnisotropicParticle(SPHParticle* particle);

	float weight;
	Math::Vector3d<float> weightedPosition;
	Math::Vector3d<float> updatePosition;
	SPHParticle* particle;
};

class SurfaceBuilder
{
public:
	SurfaceBuilder() = default;

	SurfaceBuilder(const std::vector<SPHParticle*>& sphParticles);

	~SurfaceBuilder();

	void clear();

	void updatePosition(const float effectLength);

private:
	std::vector<SPHParticle*> sphParticles;
	std::vector<AnisotropicParticle*> aniParticles;

};
	}
}

#endif