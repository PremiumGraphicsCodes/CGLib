#include "BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BubbleParticle::BubbleParticle(PBSPHParticle* parent) :
	parent(parent),
	totalTrappedAirPotential(0.0f),
	totalWaveCrestPotential(0.0f),
	kineticEnergyPotential(0.0f)
{}


Vector3d<float> BubbleParticle::getNormalizedDistance(const PBSPHParticle& rhs) const
{
	return (this->getPosition() - rhs.getPosition()).normalized();
}

Vector3d<float> BubbleParticle::getNormalizedVelocity(const PBSPHParticle& rhs) const
{
	const auto vDiff = this->getVelocity() - rhs.getVelocity();
	if (vDiff.isZero()) {
		return Vector3d<float>(0, 0, 0);
	}
	return vDiff.normalized();
}

float BubbleParticle::getDistance(const PBSPHParticle& rhs) const
{
	return rhs.getPosition().getDistance(this->getPosition());
}

float BubbleParticle::getCurvature(const PBSPHParticle& rhs, const float effectRadius) const
{
	const auto dist = getDistance(rhs);
	const auto curvature = 1.0f - this->getNormal().getInnerProduct(rhs.getNormal()) * getWeight(dist, effectRadius);
	const auto dif = (rhs.getPosition() - this->getPosition()).normalized();
	const auto innerProduct = dif.getInnerProduct(this->getNormal());
	if (innerProduct >= 0.0f) {
		return 0.0f;
	}
	else {
		return curvature;
	}
}

float BubbleParticle::getTrappedAirPotential(const PBSPHParticle& rhs, const float effectRadius) const
{
	const auto& vDiff = getNormalizedVelocity(rhs);
	const auto& pDiff = getNormalizedDistance(rhs);
	const auto vLength = vDiff.getLength();
	const auto dist = getDistance(rhs);
	return vLength * (1.0f - vDiff.getInnerProduct(pDiff) ) * getWeight(dist, effectRadius);
}

float BubbleParticle::getWeight(const float distance, const float effectRadius) const
{
	if (distance > effectRadius) {
		return 0.0f;
	}
	return 1.0f - distance / effectRadius;
}

float BubbleParticle::getMovingDirectionCoe() const
{
	return getVelocity().getInnerProduct(getNormal());
}

float BubbleParticle::getMovingDelta() const
{
	const auto coe = getMovingDirectionCoe();
	if (coe < 0.6f) {
		return 0.0f;
	}
	else {
		return 1.0f;
	}
}

float BubbleParticle::getKineticEnegy() const
{
	return 0.5f * getMass() * getVelocity().getLengthSquared();
}

namespace {
	float clamp(float v, float min, float max) {
		const auto numerator = std::min<float>(v, max) - std::min<float>(v, min);
		const auto denominator = max - min;
		return numerator / denominator;
	}
}

void BubbleParticle::solveTrappedAirPotential(const float effectRadius)
{
	totalTrappedAirPotential = 0.0f;
	const auto& neighbors = getNeighbors();
	for (auto n : neighbors) {
		totalTrappedAirPotential += getTrappedAirPotential(*n, effectRadius);
	}
}

void BubbleParticle::clampTrappedAirPotential(const float min_, const float max_)
{
	totalTrappedAirPotential = clamp(totalTrappedAirPotential, min_, max_);
}


void BubbleParticle::solveWaveCrestPotential(const float effectRadius)
{
	totalWaveCrestPotential = 0.0f;
	const auto& neighbors = getNeighbors();
	for (auto n : neighbors) {
		totalWaveCrestPotential += getCurvature(*n, effectRadius);
	}
}

void BubbleParticle::clampWaveCrestPotential(const float min_, const float max_)
{
	totalWaveCrestPotential = clamp(totalWaveCrestPotential, min_, max_);
}

void BubbleParticle::solveKineticEnergy()
{
	kineticEnergyPotential = getKineticEnegy();
}

void BubbleParticle::clampKineticEnegyPotential(const float min_, const float max_)
{
	kineticEnergyPotential = clamp(kineticEnergyPotential, min_, max_);
}

float BubbleParticle::getGenerateParticleNumber(const float trappedAirCoe, const float waveCrestCoe, const float dt) const
{
	return kineticEnergyPotential * (trappedAirCoe * totalTrappedAirPotential + waveCrestCoe * totalWaveCrestPotential) * dt;
}

BubbleParticle::Type BubbleParticle::getType() const
{
	const auto neighborSize = getNeighbors().size();
	if (neighborSize < 6) {
		return BubbleParticle::Type::Spray;
	}
	else if (neighborSize > 20) {
		return BubbleParticle::Type::Air;
	}
	else {
		return BubbleParticle::Type::Foam;
	}
}

float BubbleParticle::getMass() const
{
	return parent->getMass();
}


#include "TinyBubbleParticle.h"
#include "TinyFoamParticle.h"
#include "TinySprayParticle.h"

std::list<ITinyParticle*> BubbleParticle::generateTinyParticles(const int howMany)
{
	std::list<ITinyParticle*> results;
	const auto type = getType();
	if (type == Type::Spray) {
		for (int i = 0; i < howMany; ++i) {
			auto p = new TinySprayParticle(this->getPosition(), this->getVelocity(), this);
			results.push_back(p);
		}
	}
	else if (type == Type::Foam) {
		for (int i = 0; i < howMany; ++i) {
			auto p = new TinyFoamParticle(this->getPosition(), this->getVelocity(), this);
			results.push_back(p);
		}
	}
	else if (type == Type::Air) {
		for (int i = 0; i < howMany; ++i) {
			auto p = new TinyBubbleParticle(this->getPosition(), this->getVelocity(), this);
			results.push_back(p);
		}
	}
	else {
		assert(false);
	}
	return results;
}