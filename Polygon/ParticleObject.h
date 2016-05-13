#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "Vertex.h"
#include "../Math/Sphere.h"
#include "../Math/Box3d.h"
#include "../Math/Index3d.h"
#include "Particle.h"

namespace Crystal {
	namespace Polygon {

class PolygonMesh;
class Particle;
class Volume;

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

	void add(const Math::Box3d<float>& box, const float particleDiameter, const float charge = 1.0f);

	~ParticleObject();

	void sort();

	Math::Box3d<float> getBoundingBox() const;

	std::vector<Particle*> getParticles() const { return particles; }

	PolygonMesh* toPolygon(const float isolevel, const float effectLength, const Math::Space3d<float>& space) const;

private:

	std::vector<Particle*> getIntersection(const ParticleObject& rhs) const;

	std::vector<Particle*> particles;
};
	}
}

#endif