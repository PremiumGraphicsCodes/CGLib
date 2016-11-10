#include "BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


Vector3d<float> BubbleParticle::getNormalizedDistance(const BubbleParticle& rhs) const
{
	return (this->position - rhs.position).normalized();
}

Vector3d<float> BubbleParticle::getNormalizedVelocity(const BubbleParticle& rhs) const
{
	const auto vDiff = this->velocity - rhs.velocity;
	if (vDiff.isZero()) {
		return Vector3d<float>(0, 0, 0);
	}
	return vDiff.normalized();
}

float BubbleParticle::getDistance(const BubbleParticle& rhs) const
{
	return rhs.position.getDistance(this->position);
}

float BubbleParticle::getCurvature(const BubbleParticle& rhs, const float effectRadius) const
{
	const auto dist = getDistance(rhs);
	const auto curvature = 1.0f - this->normal.getInnerProduct(rhs.normal) * getWeight(dist, effectRadius);
	const auto innerProduct = rhs.getNormalizedDistance(*this).getInnerProduct(this->normal);
	if (innerProduct >= 0.0f) {
		return 0.0f;
	}
	else {
		return curvature;
	}
}

float BubbleParticle::getTrappedAirPotential(const BubbleParticle& rhs, const float effectRadius) const
{
	const auto& vDiff = getNormalizedVelocity(rhs);
	const auto& pDiff = getNormalizedDistance(rhs);
	const auto vLength = vDiff.getLength();
	const auto dist = getDistance(rhs);
	return vLength * (1.0 - vDiff.getInnerProduct(pDiff) ) * getWeight(dist, effectRadius);
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
	return velocity.getInnerProduct(normal);
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

float BubbleParticle::getKineticEnegy(const float mass) const
{
	return 0.5f * mass * velocity.getLengthSquared();
}
