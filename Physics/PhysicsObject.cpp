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
