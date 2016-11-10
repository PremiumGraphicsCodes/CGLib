#pragma once

#include "ParticlePair.h"

namespace Crystal {
	namespace Physics {


class BubbleGenerator
{
public:
	BubbleGenerator(const std::vector<SPHParticlePair>& pairs, const float effectRadius);


private:
	float effectRadius;
};
	}
}