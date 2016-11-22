#include "BubbleGenerator.h"
#include "ITinyParticle.h"

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
	clear();
}

void BubbleGenerator::clear()
{
	for (auto b : bubbleParticles) {
		delete b;
	}
	bubbleParticles.clear();

	for (auto t : tinyParticles) {
		delete t;
	}
	tinyParticles.clear();
}


void BubbleGenerator::generate(const float effectRadius, const float dt)
{
	for (auto b : bubbleParticles) {
		b->solveTrappedAirPotential(effectRadius);
		b->solveWaveCrestPotential(effectRadius);
		b->solveKineticEnergy();
		//b->clampTrappedAirPotential();
		//b->clampWaveCrestPotential();
	}
	for (auto b : bubbleParticles) {
		const auto howMany = b->getGenerateParticleNumber(1.0, 1.0, dt);
		const auto newTinies = b->generateTinyParticles(howMany);
		tinyParticles.insert(tinyParticles.end(), newTinies.begin(), newTinies.end());
	}
}

void BubbleGenerator::proceedTime(const Vector3d<float>& externalForce, const float dt)
{
	for (auto t : tinyParticles) {
		t->integrate(externalForce, dt);
	}
}

void BubbleGenerator::deleteExpireds()
{
	auto newEnd = std::remove_if(
		tinyParticles.begin(),
		tinyParticles.end(),
		[](ITinyParticle* p)->bool{ return p->isExpired(); }
	);
	for (auto iter = newEnd; iter != tinyParticles.end(); ++iter) {
		tinyParticles.erase(iter);
		delete *iter;
	}
}
