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
