#include "PointBuffer.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/Particle.h"
#include "../Polygon/Actor.h"
#include "../Polygon/Joint.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;

Point::Point(const Particle& particle, const unsigned int id)
{
	position = particle.getPosition();
	color = ColorRGBA<float>(1.0, 1.0, 0.0, particle.getDensity());
	size = particle.getDiameter();
	this->id = id;
}

Point::Point(const Joint& joint, const unsigned int id)
{
	position = joint.getPosition();
	color = ColorRGBA<float>(1.0, 1.0, 1.0, 1.0f);
	size = 1.0f;//joint.getDiameter();
	this->id = id;
}


PointBuffer::PointBuffer(const ParticleObject& object)
{
	add(object);
}

void PointBuffer::add(const ParticleObject& object)
{
	const auto& particles = object.getParticles();
	for (size_t i = 0; i < particles.size(); ++i) {
		add(Point(*particles[i], ids.size()));
	}

}

void PointBuffer::add(const ActorObject& actor)
{
	const auto joints = actor.getJoints();
	for (auto& j : joints) {
		add(Point(*j, ids.size()));
	}
}



void PointBuffer::clear()
{
	position.clear();
	color.clear();
	sizes.clear();
	ids.clear();
}



void PointBuffer::add(const Point& point)
{
	position.add(point.getPosition());
	color.add(point.getColor());
	sizes.add(point.getSize());
	ids.push_back(point.getId());
}

