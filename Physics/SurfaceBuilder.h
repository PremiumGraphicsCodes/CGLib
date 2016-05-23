#ifndef __CRYSTAL_PHYSICS_SURFACE_BUILDER_H__
#define __CRYSTAL_PHYSICS_SURAFCE_BUILDER_H__

#include "SPHParticle.h"

namespace Crystal {
	namespace Physics {

class AnisotropicParticle : public Polygon::Particle
{
public:
	AnisotropicParticle(const Math::Vector3d<float>& position, const float density, const float radius);

	float weight;
	Math::Vector3d<float> weightedPosition;
	Math::Matrix3d<float> matrix;
	//Math::Vector3d<float> updatePosition;
};

class SurfaceBuilder
{
public:
	SurfaceBuilder() = default;

	SurfaceBuilder(const std::vector<Polygon::Particle*>& sphParticles);

	~SurfaceBuilder();

	void clear();

	void updatePosition(const float effectLength);

	std::vector<AnisotropicParticle*> getAniParticles() { return aniParticles; }

private:
	std::vector<Polygon::Particle*> sphParticles;
	std::vector<AnisotropicParticle*> aniParticles;
};

	}
}

#endif