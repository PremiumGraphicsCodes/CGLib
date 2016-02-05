#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "Vertex.h"
#include "../Math/Sphere.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Polygon {

		class PolygonObject;

class Particle
{
public:
	Particle(const Math::Vector3d<float>& position) :
		position(position),
		value(0)
	{}

	Particle(const Math::Vector3d<float>& position, const float value) :
		position(position),
		value(value)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	float getValue() const { return value; }

	Particle* clone() { 
		return new Particle(position, value);
	}

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }

private:
	Math::Vector3d<float> position;
	float value;
	float radius;
};

class ParticleObject
{
public:
	ParticleObject() :
		radius(0.5)
	{
		sort();
	}

	ParticleObject(const std::vector<Particle*>& particles) :
		particles(particles),
		radius(0.5)
	{
		sort();
	}

	ParticleObject(const std::vector<Math::Vector3d<float>>& positions);

	ParticleObject(const Math::Sphere<float>& sphere, const float diameter);

	~ParticleObject();

	void sort();

	Math::Box<float> getBoundingBox() const;

	//PolygonObject* toPolygonObject() const;

	//void add(const ParticleObject& rhs);

	//void sub(const ParticleObject& rhs);

	ParticleObject* createUnion(const ParticleObject& rhs);

	ParticleObject* createSub(const ParticleObject& rhs);

	ParticleObject* createIntersection(const ParticleObject& rhs);

	float getDiameter() const { return radius * 2.0f; }

	std::vector<Particle*> getParticles() const { return particles; }

private:
	std::vector<Particle*> getUnion(const ParticleObject& rhs) const;

	std::vector<Particle*> getSub(const ParticleObject& rhs) const;

	std::vector<Particle*> getIntersection(const ParticleObject& rhs) const;


	std::vector<Particle*> particles;
	const float radius;
};
	}
}

#endif