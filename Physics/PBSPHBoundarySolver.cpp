#include "PBSPHBoundarySolver.h"

#include "PBSPHParticle.h"
#include "../Math/SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	SPHKernel<float> kernel;
}

PBSPHBoundarySolver::PBSPHBoundarySolver(const Box3d<float>& boundary) :
	boundary(boundary)
{
}


void PBSPHBoundarySolver::solveDensity(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto v = getOverVector(particles[i]->getPosition());
		particles[i]->addDensity(v.getLength(), particles[i]->getMass());
	}
}

void PBSPHBoundarySolver::solveCorrectPosition(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto v = getOverVector(particles[i]->getPosition());
		particles[i]->addPositionCorrection(-v);
	}
}


Vector3d<float> PBSPHBoundarySolver::getOverVector(const Vector3d<float>& position)
{
	return Vector3d<float>(getOverX(position.getX()), getOverY(position.getY()), getOverZ(position.getZ()));
}

float PBSPHBoundarySolver::getOverX(const float x)
{
	float over = 0;
	if (x > boundary.getMaxX()) {
		over = x - boundary.getMaxX();
	}
	else if (x < boundary.getMinX()) {
		over = x - boundary.getMinX();
	}
	return over;
}

float PBSPHBoundarySolver::getOverY(const float y)
{
	float over = 0;
	if (y > boundary.getMaxY()) {
		over = y - boundary.getMaxY();
	}
	else if (y < boundary.getMinY()) {
		over = y - boundary.getMinY();
	}
	return over;
}

float PBSPHBoundarySolver::getOverZ(const float z)
{
	float over = 0;
	if (z > boundary.getMaxZ()) {
		over = z - boundary.getMaxZ();
	}
	else if (z < boundary.getMinZ()) {
		over = z - boundary.getMinZ();
	}
	return over;
}

