#ifndef __CRYSTAL_PHYSICS_TINY_PARTICLE_H__
#define __CRYSTAL_PHYSICS_TINY_PARTICLE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Physics {
		class BubbleParticle;

class ITinyParticle
{
public:
	ITinyParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, BubbleParticle* parent);

	void integrate(const Math::Vector3d<float>& externalForce, const float dt);

	virtual void updateVelocity(const float dt, const Math::Vector3d<float>& gravity) = 0;

	Math::Vector3d<float> getAveragedLocalVelocity() const;

	Math::Vector3d<float> getVelocity() const { return velocity; }

	Math::Vector3d<float> getPosition() const { return position; }

protected:
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> position;
	float mass;
	BubbleParticle* parent;

};

class TinySprayParticle : public ITinyParticle
{
public:
	TinySprayParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, BubbleParticle* parent);

	void updateVelocity(const float dt, const Math::Vector3d<float>& gravity) override;

private:
};

class TinyFoamParticle : public ITinyParticle
{
public:
	TinyFoamParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, BubbleParticle* parent);

	void updateVelocity(const float dt, const Math::Vector3d<float>& gravity) override;

private:
};

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