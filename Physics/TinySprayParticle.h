#ifndef __CRYSTAL_PHYSICS_TINY_SPRAY_PARTICLE_H__
#define __CRYSTAL_PHYSICS_TINY_SPRAY_PARTICLE_H__

#include "ITinyParticle.h"

namespace Crystal {
	namespace Physics {

class TinySprayParticle : public ITinyParticle
{
public:
	TinySprayParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, BubbleParticle* parent);

	void updateVelocity(const float dt, const Math::Vector3d<float>& gravity) override;
};
	}
}

#endif