#include "SurfaceBuilder.h"

#include "SPHParticle.h"

#include "IndexedFinder.h"

#include "../Polygon/SpaceHash.h"


using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

namespace {
	float getWeight(const float distance, const float effectLength) {
		return 1.0f - std::pow(distance / effectLength, 3);
	}
}

AnisotropicParticle::AnisotropicParticle(const Vector3d<float>& pos, const float density, const float radius) :
	Particle(pos, density, radius),
	weight(0)
{
	matrix = Matrix3d<float>(0, 0, 0, 0, 0, 0, 0, 0, 0);
	//moveTo( (1.0f - 0.9f) * pos );
}


SurfaceBuilder::SurfaceBuilder(const std::vector<Particle*>& sphParticles)
{
	for (auto& p : sphParticles) {
		auto ap = new AnisotropicParticle(p->getPosition(), p->getDensity(), p->getRadius());
	 	aniParticles.push_back( ap );
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


void SurfaceBuilder::updatePosition(const float effectLength)
{
	SpaceHash hash(effectLength, static_cast<int>(aniParticles.size()));
	for (auto& p : aniParticles) {
		hash.add(p);
	}
	for (auto& p : aniParticles) {
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			if (n == p) {
				continue;
			}
			auto distance = n->getPosition().getDistance(p->getPosition());
			auto weight = ::getWeight(distance, effectLength);
			p->weight += weight;
			p->weightedPosition += n->getPosition() * weight;
		}
	}
	for (auto& p : aniParticles) {
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			if (n == p) {
				continue;
			}

			auto distance = n->getPosition().getDistance(p->getPosition());
			p->weightedPosition /= p->weight;//  ::getWeight(distance, effectLength);
		}
	}
	for (auto& p : aniParticles) {
		//p->move( 0.9f * p->weightedPosition );
		//p->move( 1.0 * p->weightedPosition );
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			if (n == p) {
				continue;
			}
			auto distance = n->getPosition().getDistance(p->getPosition());
			auto weight = ::getWeight(distance, effectLength);
			auto v = p->getPosition() - n->getPosition();
			auto x = v.getX();
			auto y = v.getY();
			auto z = v.getZ();

			Matrix3d<float> m(
				x*x, x*y, x*z,
				x*y, y*y, y*z,
				x*z, y*z, z*z);
			m.scale(weight / p->weight);
			p->matrix += m;
		}
	}
}
