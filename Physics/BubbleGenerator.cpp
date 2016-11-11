#include "BubbleGenerator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BubbleGenerator::BubbleGenerator(const std::vector<PBSPHParticle*>& originalParticles)
{
	for (auto particle : originalParticles) {
		auto newParticle = new BubbleParticle(particle);
		bubbleParticles.push_back(newParticle);
	}
}


BubbleGenerator::~BubbleGenerator()
{
	for (auto b : bubbleParticles) {
		delete b;
	}
}

void BubbleGenerator::generate(const float effectRadius, const float dt)
{
	for (auto b : bubbleParticles) {
		b->solveTrappedAirPotential(effectRadius);
		b->solveWaveCrestPotential(effectRadius);
	}
	for (auto b : bubbleParticles) {
		b->getGenerateParticleNumber(1.0, 1.0, dt);
	}
}
