#include "OrientedParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

namespace {
	float getWeight(const float dist, const float radius) {
		if (dist < radius) {
			return 1.0f - std::pow(dist / radius, 3);
		}
		return 0.0f;
	}
}

Matrix3d<float> OrientedParticle::getCovarianceMatrix() const
{
	const auto& weightedMeanPosition = getWeightedMeanPosition();
	Matrix3d<float> matrix;
	for (auto n : neighbors) {
		const auto v = n->getPosition() - weightedMeanPosition;
		const auto xx = v.getX() * v.getX();
		const auto xy = v.getX() * v.getY();
		const auto xz = v.getX() * v.getZ();

		const auto yx = xy;
		const auto yy = v.getY() * v.getY();
		const auto yz = v.getY() * v.getZ();

		const auto zx = xz;
		const auto zy = yz;
		const auto zz = v.getZ() * v.getZ();

		Matrix3d<float> m(
			xx, xy, xz,
			yx, yy, yz,
			zx, zy, zz);
		const auto weight = getWeight(n);
		m.scale( weight );
		matrix += m;
	}
	matrix.scale( 1.0f / getTotalWeight());
	return matrix;
}

Vector3d<float> OrientedParticle::getWeightedMeanPosition() const
{
	Vector3d<float> weightedPosition;
	for (auto n : neighbors) {
		weightedPosition += getWeight(n) * n->getPosition();
	}
	const auto totalWeight = getTotalWeight();
	return weightedPosition / totalWeight;
}

float OrientedParticle::getTotalWeight() const
{
	float totalWeight = 0.0f;
	for (auto n : neighbors) {
		totalWeight += getWeight(n);
	}
	return totalWeight;
}

float OrientedParticle::getWeight(IParticle* particle) const
{
	const auto dist = particle->getPosition().getDistance(position);
	return ::getWeight(dist, radius);
}
