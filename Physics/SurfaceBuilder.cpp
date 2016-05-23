#include "SurfaceBuilder.h"

#include "SPHParticle.h"

#include "IndexedFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	float getWeight(const float distance, const float effectLength) {
		return 1.0f - std::pow(distance / effectLength, 3);
	}
}

AnisotropicParticle::AnisotropicParticle(SPHParticle* particle) :
	particle(particle),
	weight(0)
{
	updatePosition = (1.0f - 0.9f) * particle->getPosition();
}


SurfaceBuilder::SurfaceBuilder(const std::vector<SPHParticle*>& sphParticles) :
	sphParticles(sphParticles)
{
	for (auto& p : sphParticles) {
	 	aniParticles.push_back( new AnisotropicParticle(p) );
	}
}

SurfaceBuilder::~SurfaceBuilder()
{
	clear();
}

void SurfaceBuilder::clear()
{
	for (auto& n : aniParticles) {
		delete n;
	}
	aniParticles.clear();
}

#include "../Polygon/SpaceHash.h"
using namespace Crystal::Polygon;

void SurfaceBuilder::updatePosition(const float effectLength)
{
	SpaceHash hash(effectLength, static_cast<int>(aniParticles.size()));
	for (auto& p : aniParticles) {
		hash.add(p);
	}
	for (auto& p : aniParticles) {
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			auto distance = n->getPosition().getDistance(p->getPosition());
			auto weight = ::getWeight(distance, effectLength);
			p->weight += weight;
			p->weightedPosition += p->getPosition() * weight;
		}
	}
	for (auto& p : aniParticles) {
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			auto distance = n->getPosition().getDistance(p->getPosition());
			p->weightedPosition /= p->weight;//  ::getWeight(distance, effectLength);
		}
	}
	for (auto& p : aniParticles) {
		p->updatePosition += 0.9f * p->weightedPosition;
	}
}
