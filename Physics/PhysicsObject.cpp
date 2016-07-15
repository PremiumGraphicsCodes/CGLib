#include "PhysicsObject.h"
#include "SPHParticle.h"

#include "../Core/ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;


PhysicsObject::PhysicsObject(const std::vector<SPHParticle*>& particles) :
	particles(particles),
	nextId(0)
{
}

PhysicsObject::PhysicsObject(const Box3d<float>& box, const float divideLength, const SPHConstant& constant):
	constant(constant),
	nextId(0)
{
	const auto points = box.toPoints(divideLength);
	for (const auto& pos : points) {
		SPHParticle* p = new SPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
	}
}

PhysicsObject::PhysicsObject(const Sphere<float>& sphere, const float divideLength, const SPHConstant& constant) :
	nextId(0)
{
	const auto points = sphere.toPoints(divideLength);
	for (const auto& pos : points) {
		SPHParticle* p = new SPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
	}

}


PhysicsObject::~PhysicsObject()
{
	clear();
}

SPHParticle* PhysicsObject::createParticle(const Vector3d<float>& position, const Vector3d<float>& velocity)
{
	auto p = new SPHParticle(position, constant.getEffectLength() / 1.25f / 2.0f, &constant, nextId++);
	p->setVelocity(velocity);
	particles.push_back(p);
	return p;
}


std::vector<SPHParticle*> PhysicsObject::createParticles(const Box3d<float>& box, const float divideLength)
{
	std::vector<SPHParticle*> newParticles;
	const auto points = box.toPoints(divideLength);
	for (const auto& pos : points) {
		SPHParticle* p = new SPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
		newParticles.push_back(p);
	}
	return newParticles;
}

std::vector<SPHParticle*> PhysicsObject::createParticles(const Sphere<float>& sphere, const float divideLength)
{
	std::vector<SPHParticle*> newParticles;

	const auto points = sphere.toPoints(divideLength);
	for (const auto& pos : points) {
		SPHParticle* p = new SPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
		newParticles.push_back(p);
	}
	return newParticles;
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
		center += p->getPosition();
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

void PhysicsObject::move(const Vector3d<float>& v)
{
	for (const auto& p : particles) {
		p->move(v);
	}
}

void PhysicsObject::setVelocity(const Vector3d<float>& velocity)
{
	for (const auto& p : particles) {
		p->setVelocity(velocity);
	}

}

ParticleObject* PhysicsObject::toParticleObject() const
{
	std::vector<IParticle*> ps;
	for (size_t i = 0; i < particles.size(); ++i) {
		ps.push_back(particles[i]->clone());
	}
	return new ParticleObject(ps);
}

ParticleObject* PhysicsObject::toSurfaceParticleObject() const
{
	std::vector<IParticle*> ps;
	for (int i = 0; i < particles.size(); ++i) {
		const auto length = particles[i]->getNormal().getLength();
		const auto normal = particles[i]->getNormal().normalized();
		const auto innerProd = normal.getInnerProduct(Vector3d<float>(0.0f, 0.0f, 1.0f));

		if ( length > 0.20f && innerProd > 0.0f) {
			ps.push_back(particles[i]->clone());
		}
	}
	return new ParticleObject(ps);

}

/*
PolygonMesh* PhysicsObject::toPolygonObject(const float isolevel, const int levelOfDetail, const Space3d<float>& space) const
{
	std::unique_ptr<ParticleObject> particleObject( toParticleObject() );
	return particleObject->toPolygon(isolevel, levelOfDetail, space);
}
*/
