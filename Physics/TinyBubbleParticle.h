#ifndef __CRYSTAL_PHYSICS_TINY_BUBBLE_PARTICLE_H__
#define __CRYSTAL_PHYSICS_TINY_BUBBLE_PARTICLE_H__

#include "ITinyParticle.h"

namespace Crystal {
	namespace Physics {

class TinyBubbleParticle : public ITinyParticle
{
public:
	TinyBubbleParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, BubbleParticle* parent);

	void updateVelocity(const float dt, const Math::Vector3d<float>& gravity) override;

private:
};

	}
}

#endif