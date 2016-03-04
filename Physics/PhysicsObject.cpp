#include "PhysicsObject.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


PhysicsObject::PhysicsObject(const std::vector<Particle*>& particles) :
	particles(particles)
{}


PhysicsObject::~PhysicsObject()
{
	clear();
}

float PhysicsObject::getMass() const
{
	auto weight = 0.0f;
	for (const auto& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

float PhysicsObject::getRestVolume() const
{
	auto volume = 0.0f;
	for (const auto& particle : particles) {
		volume += particle->getRestVolume();
	}
	return volume;
}

void PhysicsObject::forwardTime(const float timeStep)
{
	for (const auto& p : particles) {
		p->forwardTime(timeStep);
	}
}

void PhysicsObject::addExternalForce(const Vector3d<float>& externalForce)
{
	for (const auto& p : particles) {
		p->addExternalForce(externalForce);
	}
}

Vector3d<float> PhysicsObject::getCenter() const
{
	if (particles.empty()) {
		return Math::Vector3d<float>(0.0, 0.0, 0.0);
	}
	Math::Vector3d<float> center(0.0, 0.0, 0.0);
	for (const auto& p : particles) {
		center += p->getCenter();
	}
	return center /= static_cast<float>(particles.size());
}

Vector3d<float> PhysicsObject::getAverageVelosity() const
{
	Math::Vector3d<float> averageVelosity(0.0, 0.0, 0.0);
	for (const auto& p : particles) {
		averageVelosity += p->getVelocity();// variable.velocity;
	}
	return averageVelosity / static_cast<float>(particles.size());
}

float PhysicsObject::getWeight() const
{
	auto weight = 0.0f;
	for (const auto& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

void PhysicsObject::convertToFluidForce()
{
	Math::Vector3d<float> totalForce(0.0, 0.0, 0.0);
	for (const auto& p : particles) {
		totalForce += p->getForce() * p->getVolume();
	}

	const float weight = getWeight();
	for (const auto& p : particles) {
		p->setForce(totalForce / weight * p->getDensity());
	}
}
