#include "BubbleGenerator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BubbleGenerator::BubbleGenerator(const std::vector<PBSPHParticle*>& originalParticles)
{
	for (auto particle : originalParticles) {
		const auto& p = particle->getPosition();
		const auto& v = particle->getVelocity();
		const auto& n = particle->getNormal();
		const auto m = particle->getMass();
		auto newParticle = new BubbleParticle(p, v, n, m);
		bubbleParticles.push_back(newParticle);
	}
	//for (auto particle : originalParticles) {
	for (int i = 0; i < originalParticles.size(); ++i) {
		const auto originalParticle = originalParticles[i];
		const auto bubbleParticle = bubbleParticles[i];
		const auto& neighbors = originalParticle->getNeighbors();
		std::list<BubbleParticle*> ns;
		for (auto n : neighbors) {
			ns.push_back( bubbleParticles[n->getId()] );
		}
		bubbleParticle->setNeighbors(ns);
	}
}

void BubbleGenerator::add(BubbleParticle* b)
{
	bubbleParticles.push_back(b);
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
