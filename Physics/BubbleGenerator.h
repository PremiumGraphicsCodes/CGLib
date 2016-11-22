#pragma once

#include "ParticlePair.h"

#include "BubbleParticle.h"
#include "PBSPHParticle.h"
#include "PBSPHParticlePair.h"

namespace Crystal {
	namespace Physics {
		class ITinyParticle;

class BubbleGenerator
{
public:
	BubbleGenerator(const std::vector<PBSPHParticle*>& originalParticles);

	~BubbleGenerator();

	void clear();

	void generate(const float effectRadius, const float dt);

	void proceedTime(const Math::Vector3d<float>& externalForce, const float dt);

	void deleteExpireds();

	std::vector<ITinyParticle*> getTinys() { return tinyParticles; }

private:
	std::vector<BubbleParticle*> bubbleParticles;
	std::vector<ITinyParticle*> tinyParticles;
	float effectRadius;
};
	}
}