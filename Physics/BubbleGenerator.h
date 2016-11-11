#pragma once

#include "ParticlePair.h"

#include "BubbleParticle.h"
#include "PBSPHParticle.h"
#include "PBSPHParticlePair.h"

namespace Crystal {
	namespace Physics {


class BubbleGenerator
{
public:
	BubbleGenerator(const std::vector<PBSPHParticle*>& originalParticles);

	void add(BubbleParticle* b);

	~BubbleGenerator();

	void generate(const float effectRadius, const float dt);

private:
	std::vector<BubbleParticle*> bubbleParticles;
	float effectRadius;
};
	}
}