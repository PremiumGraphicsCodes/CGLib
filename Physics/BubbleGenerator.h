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
	BubbleGenerator() = default;

	BubbleGenerator(const std::vector<PBSPHParticle*>& originalParticles);

	~BubbleGenerator();

	void add(const std::vector<PBSPHParticle*>& originalParticles);

	void clear();

	void solvePotentials(const float effectRadius);

	void clampPotentials();

	void generate(const float dt);

	void proceedTime(const Math::Vector3d<float>& externalForce, const float dt);

	std::list<ITinyParticle*> getExpireds() const;

	void remove(const std::list<ITinyParticle*>& particles);

	void deleteExpireds();

	std::list<ITinyParticle*> getTinys() { return tinyParticles; }

	void sortByLifeTime();

private:
	std::vector<BubbleParticle*> bubbleParticles;
	std::list<ITinyParticle*> tinyParticles;
};
	}
}