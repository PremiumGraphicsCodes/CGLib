#include "PhysicsObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


PhysicsObject::PhysicsObject(const std::vector<Particle*>& particles) :
	particles(particles)
{}

PhysicsObject::PhysicsObject(const std::vector<Particle*>& particles, const CoordinatorSPtrVector& coordinators) :
	particles(particles),
	coordinators(coordinators)
{}

PhysicsObject::~PhysicsObject()
{
	clear();
}

void PhysicsObject::coordinate() const
{
	for (const auto& coordinator : coordinators) {
		coordinator->coordinate(particles);
	}
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
