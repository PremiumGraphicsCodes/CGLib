#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "stdafx.h"
#include "Vertex.h"
#include "Particle.h"

namespace Crystal {
	namespace Core {

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

	ParticleObject(const std::vector<IParticle*>& particles) :
		particles(particles)
	{
		sort();
	}

	void add(const Particle& particle);

	void add(IParticle* particle);

	void add(const Math::Sphere<float>& sphere, const float particleDiameter, const float charge = 1.0f);

	void add(const Math::Box3d<float>& box, const float particleDiameter, const float charge = 1.0f);

	~ParticleObject();

	void sort();

	Math::Box3d<float> getBoundingBox() const;

	std::vector<IParticle*> getParticles() const { return particles; }

	PolygonMesh* toPolygon(const float isolevel, const int levelOfDetail, const Math::Space3d<float>& space) const;

	std::vector<Math::Ellipsoid<float>> toEllipsoids() const;

private:

	std::vector<IParticle*> getIntersection(const ParticleObject& rhs) const;

	std::vector<IParticle*> particles;
};
	}
}

#endif