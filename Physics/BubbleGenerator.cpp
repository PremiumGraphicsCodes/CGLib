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
	sortByLifeTime();
}

void BubbleGenerator::proceedTime(const Vector3d<float>& externalForce, const float dt)
{
	for (auto t : tinyParticles) {
		t->integrate(externalForce, dt);
	}
	sortByLifeTime();
}

void BubbleGenerator::sortByLifeTime()
{
	tinyParticles.sort(
		[](ITinyParticle* p1, ITinyParticle* p2)->bool { return p1->getLifeTime() < p2->getLifeTime(); }
	);

}

std::list<ITinyParticle*> BubbleGenerator::getExpireds() const
{
	std::list<ITinyParticle*> results;
	for (auto p : tinyParticles) {
		if (p->isExpired()) {
			results.push_back(p);
		}
	}
	return results;
}

void BubbleGenerator::remove(const std::list<ITinyParticle*>& particles)
{
	for (auto p : particles) {
		auto ptr = p;
		tinyParticles.remove(p);
		delete ptr;
	}
}

void BubbleGenerator::deleteExpireds()
{
	remove(getExpireds());
}
