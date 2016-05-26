#include "SurfaceBuilder.h"

#include "SPHParticle.h"

#include "IndexedFinder.h"

#include "../Polygon/SpaceHash.h"
#include "../Math/Matrix.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
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

Matrix3d<float> AnisotropicParticle::getAnisotoropicMatrix()
{
	Matrix<3, 3, float> m(matrix.toArray3x3());
	JacobiSolver<3, 3, float> solver(m);
	const auto& eigenValues = solver.solve(1.0e-6);
	const auto& orthogonalMatrix = solver.getOrthogonalMatrix();
	Matrix3d<float> rotationMatrix(orthogonalMatrix.a);

	const float kr = 4.0f;
	const float ks = 1400.0f;
	Matrix3d<float> eigenMatrix;
	for (int i = 0; i < 3; ++i) {
		auto value = ks * std::max<float>(eigenValues[i], eigenValues[0] / kr);
		eigenMatrix.set(i, i, value);
	}
	
	const auto& inverseEigenMatrix = eigenMatrix.getInverse();
	return rotationMatrix * inverseEigenMatrix * rotationMatrix.transposed();
}


AnisotropicParticlePair::AnisotropicParticlePair(AnisotropicParticle* p1, AnisotropicParticle* p2, const float effectLength) :
	particle1(p1),
	particle2(p2)
{
	distance = particle1->getPosition().getDistance(particle2->getPosition());

	weight = ::getWeight(getDistance(), effectLength);
	particle1->weight += weight;

	solveWeightedPosition();
	solveWeightedMatrix();
}

float AnisotropicParticlePair::getDistance() const
{
	return distance;
}

void AnisotropicParticlePair::solveWeightedPosition()
{
	particle1->weightedPosition += particle2->getPosition() * weight;
}

void AnisotropicParticlePair::solveWeightedMatrix()
{
	auto v = particle2->getPosition() - particle1->getPosition();
	auto x = v.getX();
	auto y = v.getY();
	auto z = v.getZ();

	Matrix3d<float> m(
		x*x, x*y, x*z,
		x*y, y*y, y*z,
		x*z, y*z, z*z);
	m.scale(weight);
	particle1->matrix += m;
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
	std::vector<AnisotropicParticlePair> pairs;
	for (auto& p : aniParticles) {
		auto neighbors = hash.getNeighbor(p);
		for (auto& n : neighbors) {
			auto p2 = static_cast<AnisotropicParticle*>(n);
			pairs.push_back(AnisotropicParticlePair(p, p2, effectLength));
		}
	}

	for (auto& p : aniParticles) {
		p->weightedPosition /= p->weight;
		p->matrix.scale( 1.0f / p->weight );
	}
}
