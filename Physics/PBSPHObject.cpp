#include "PBSPHObject.h"
#include "PBSPHParticle.h"
#include "../Core/ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;


PBSPHObject::PBSPHObject(const std::vector<PBSPHParticle*>& particles) :
	particles(particles),
	nextId(0)
{
}

PBSPHObject::PBSPHObject(const Box3d<float>& box, const float divideLength, const PBSPHConstant& constant) :
	constant(constant),
	nextId(0)
{
	const auto points = box.toPoints(divideLength);
	for (const auto& pos : points) {
		auto* p = new PBSPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
	}
}

PBSPHObject::PBSPHObject(const Sphere<float>& sphere, const float divideLength, const PBSPHConstant& constant) :
	nextId(0)
{
	const auto points = sphere.toPoints(divideLength);
	for (const auto& pos : points) {
		auto* p = new PBSPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
	}

}

PBSPHObject::~PBSPHObject()
{
	clear();
}

PBSPHParticle* PBSPHObject::createParticle(const Vector3d<float>& position, const Vector3d<float>& velocity)
{
	auto p = new PBSPHParticle(position, constant.getEffectLength() / 1.25f / 2.0f, &constant, nextId++);
	p->setVelocity(velocity);
	particles.push_back(p);
	return p;
}


std::vector<PBSPHParticle*> PBSPHObject::createParticles(const Box3d<float>& box, const float divideLength)
{
	std::vector<PBSPHParticle*> newParticles;
	const auto points = box.toPoints(divideLength);
	for (const auto& pos : points) {
		auto* p = new PBSPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
		newParticles.push_back(p);
	}
	return newParticles;
}

std::vector<PBSPHParticle*> PBSPHObject::createParticles(const Sphere<float>& sphere, const float divideLength)
{
	std::vector<PBSPHParticle*> newParticles;

	const auto points = sphere.toPoints(divideLength);
	for (const auto& pos : points) {
		auto* p = new PBSPHParticle(pos, divideLength*0.5f, &this->constant, nextId++);
		particles.push_back(p);
		newParticles.push_back(p);
	}
	return newParticles;
}

float PBSPHObject::getMass() const
{
	auto weight = 0.0f;
	for (const auto& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

float PBSPHObject::getRestVolume() const
{
	auto volume = 0.0f;
	for (const auto& particle : particles) {
		volume += particle->getRestVolume();
	}
	return volume;
}

void PBSPHObject::forwardTime(const float timeStep)
{
	for (const auto& p : particles) {
		p->forwardTime(timeStep);
	}
}

void PBSPHObject::addExternalForce(const Vector3d<float>& externalForce)
{
	for (const auto& p : particles) {
		p->addExternalForce(externalForce);
	}
}

Vector3d<float> PBSPHObject::getCenter() const
{
	if (particles.empty()) {
		return Math::Vector3d<float>(0.0, 0.0, 0.0);
	}
	Vector3d<float> center(0.0, 0.0, 0.0);
	for (const auto& p : particles) {
		center += p->getPosition();
	}
	return center /= static_cast<float>(particles.size());
}

Vector3d<float> PBSPHObject::getAverageVelosity() const
{
	Vector3d<float> averageVelosity(0.0, 0.0, 0.0);
	for (const auto& p : particles) {
		averageVelosity += p->getVelocity();// variable.velocity;
	}
	return averageVelosity / static_cast<float>(particles.size());
}

float PBSPHObject::getWeight() const
{
	auto weight = 0.0f;
	for (const auto& particle : particles) {
		weight += particle->getMass();
	}
	return weight;
}

void PBSPHObject::convertToFluidForce()
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

void PBSPHObject::move(const Vector3d<float>& v)
{
	for (const auto& p : particles) {
		p->move(v);
	}
}

void PBSPHObject::setVelocity(const Vector3d<float>& velocity)
{
	for (const auto& p : particles) {
		p->setVelocity(velocity);
	}
}

ParticleObject* PBSPHObject::toParticleObject() const
{
	std::vector<IParticle*> ps;
	for (size_t i = 0; i < particles.size(); ++i) {
		ps.push_back(particles[i]->clone());
	}
	return new ParticleObject(ps);
}
