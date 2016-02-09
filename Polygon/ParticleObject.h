#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "Vertex.h"
#include "../Math/Sphere.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Polygon {

class PolygonObject;
class Particle;
class MCVolume;

class ParticleObject
{
public:
	ParticleObject()
	{
		sort();
	}

	ParticleObject(const std::vector<Particle*>& particles) :
		particles(particles)
	{
		sort();
	}

	ParticleObject(const std::vector<Math::Vector3d<float>>& positions, const float diameter);

	void add(const Math::Sphere<float>& sphere, const float particleDiameter, const float charge = 1.0f);

	void add(const Math::Box<float>& box, const float particleDiameter, const float charge = 1.0f);

	~ParticleObject();

	void sort();

	Math::Box<float> getBoundingBox() const;

	//PolygonObject* toPolygonObject() const;

	//void add(const ParticleObject& rhs);

	//void sub(const ParticleObject& rhs);

	ParticleObject* createUnion(const ParticleObject& rhs);

	ParticleObject* createSub(const ParticleObject& rhs);

	ParticleObject* createIntersection(const ParticleObject& rhs);

	//float getDiameter() const { return radius * 2.0f; }

	std::vector<Particle*> getParticles() const { return particles; }

	MCVolume toVolume(const int hashTableSize) const;

private:
	std::vector<Particle*> getUnion(const ParticleObject& rhs) const;

	std::vector<Particle*> getSub(const ParticleObject& rhs) const;

	std::vector<Particle*> getIntersection(const ParticleObject& rhs) const;

	std::vector<Particle*> particles;
};
	}
}

#endif