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
		if (isBoundary(particles[i])) {
			const auto& bPos = getBoundaryPosition(particles[i]);
			const auto dist = particles[i]->getPosition().getDistance(bPos);
			particles[i]->addDensity(dist, particles[i]->getMass());
		}
	}
}

void PBSPHBoundarySolver::solveConstraintGradient(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		if (isBoundary(particles[i])) {
			const auto& bPos = getBoundaryPosition(particles[i]);
			const auto v = bPos - particles[i]->getPosition();
			particles[i]->addConstrantGradient(v);
		}
	}
}

void PBSPHBoundarySolver::solveViscosity(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto v = getOverVector(particles[i]->getPosition());
		particles[i]->solveViscosity(v.getLength());
	}
}


void PBSPHBoundarySolver::solveCorrectPosition(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		if (isBoundary(particles[i])) {
			const auto& bPos = getBoundaryPosition(particles[i]);
			const auto v = bPos - particles[i]->getPosition();
			particles[i]->addPositionCorrection(v);
		}
	}
}

void PBSPHBoundarySolver::solveForce(const std::vector<PBSPHParticle*>& particles, const float dt)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPosition());
		particles[i]->addExternalForce(-over / dt / dt);
	}
}

bool PBSPHBoundarySolver::isBoundary(PBSPHParticle* particle)
{
	const auto& pos = particle->getPosition();
	const auto& radii = particle->getRadii();
	if (pos.getX() + radii.getX() > boundary.getMaxX()) {
		return true;
	}
	if (pos.getY() + radii.getY() > boundary.getMaxY()) {
		return true;
	}
	if (pos.getZ() + radii.getZ() > boundary.getMaxZ()) {
		return true;
	}
	if (pos.getX() - radii.getX() < boundary.getMinX()) {
		return true;
	}
	if (pos.getY() - radii.getY() < boundary.getMinY()) {
		return true;
	}
	if (pos.getZ() - radii.getZ() < boundary.getMinZ()) {
		return true;
	}
	return false;
}

Vector3d<float> PBSPHBoundarySolver::getBoundaryPosition(PBSPHParticle* particle)
{
	assert(isBoundary(particle));
	const auto& pos = particle->getPosition();
	const auto& radii = particle->getRadii();
	if (pos.getX() + radii.getX() > boundary.getMaxX()) {
		return Vector3d<float>(boundary.getMaxX() + radii.getX(), pos.getY(), pos.getZ());
	}
	if (pos.getY() + radii.getY() > boundary.getMaxY()) {
		return Vector3d<float>(pos.getX(), boundary.getMaxY() + radii.getY(), pos.getZ());
	}
	if (pos.getZ() + radii.getZ() > boundary.getMaxZ()) {
		return Vector3d<float>(pos.getX(), pos.getY(), boundary.getMaxZ() + radii.getZ());
	}
	if (pos.getX() - radii.getX() < boundary.getMinX()) {
		return Vector3d<float>(boundary.getMinX() - radii.getX(), pos.getY(), pos.getZ());
	}
	if (pos.getY() - radii.getY() < boundary.getMinY()) {
		return Vector3d<float>(pos.getX(), boundary.getMinY() - radii.getY(), pos.getZ());
	}
	if (pos.getZ() - radii.getZ() < boundary.getMinZ()) {
		return Vector3d<float>(pos.getX(), pos.getY(), boundary.getMinZ() - radii.getZ());
	}
	assert(false);
	return Vector3d<float>(0, 0, 0);
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

