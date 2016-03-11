#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "Vertex.h"
#include "../Math/Sphere.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Polygon {

class PolygonObject;
class Particle;
class VolumeObject;

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

	void add(const Particle& particle);

	void add(const Math::Sphere<float>& sphere, const float particleDiameter, const float charge = 1.0f);

	void add(const Math::Box<float>& box, const float particleDiameter, const float charge = 1.0f);

	~ParticleObject();

	void sort();

	Math::Box<float> getBoundingBox() const;

	std::vector<Particle*> getParticles() const { return particles; }

	VolumeObject toVolume() const;

	PolygonObject* toPolygon(const float isolevel) const;

private:

	std::vector<Particle*> getIntersection(const ParticleObject& rhs) const;

	std::vector<Particle*> particles;
};
	}
}

#endif