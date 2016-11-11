#ifndef __CRYSTAL_PHYSICS_TINY_PARTICLE_H__
#define __CRYSTAL_PHYSICS_TINY_PARTICLE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Physics {
		class BubbleParticle;

class ITinyParticle
{
public:
	ITinyParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

	void integrate(const Math::Vector3d<float>& externalForce, const float dt);

protected:
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> position;
	float mass;
	BubbleParticle* parent;

};

class TinySprayParticle : public ITinyParticle
{
public:
	TinySprayParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

	void integrate(const Math::Vector3d<float>& externalForce, const float dt);

private:
};

class TinyFoamParticle : public ITinyParticle
{
public:
	TinyFoamParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

private:
};

class TinyBubbleParticle : public ITinyParticle
{
public:
	TinyBubbleParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

private:
};
	}
}

#endif