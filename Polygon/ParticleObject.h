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

private:
	Math::Vector3d<float> position;
	float value;
};

class ParticleObject
{
public:
	ParticleObject()
	{}

	ParticleObject(const std::vector<Math::Vector3d<float>>& positions);

	ParticleObject(const Math::Sphere<float>& sphere);

	~ParticleObject();

	Math::Box<float> getBoundingBox() const;

	//PolygonObject* toPolygonObject() const;

private:
	std::vector<Particle*> particles;
};
	}
}

#endif