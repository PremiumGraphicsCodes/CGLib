#include "PointBuffer.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/Particle.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/Joint.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;

Point::Point(const Particle& particle)
{
	position = particle.getPosition();
	color = ColorRGBA<unsigned char>(1.0, 1.0, 0.0, particle.getDensity());
	size = particle.getDiameter();
}

Point::Point(const Vertex& vertex)
{
	position = vertex.getPosition();
	color = ColorRGBA<unsigned char>(vertex.getId());
	size = 1.0f;
}


Point::Point(const Joint& joint)
{
	position = joint.getPosition();
	color = ColorRGBA<unsigned char>(1.0, 1.0, 1.0, 1.0f);
	size = 1.0f;//joint.getDiameter();
}


PointBuffer::PointBuffer(const ParticleObject& object)
{
	add(object);
}

void PointBuffer::add(const ParticleObject& object)
{
	const auto& particles = object.getParticles();
	for (size_t i = 0; i < particles.size(); ++i) {
		add(Point(*particles[i]));
	}

}

void PointBuffer::add(const ActorObject& actor)
{
	const auto joints = actor.getJoints();
	for (auto& j : joints) {
		add(Point(*j));
	}
}


void PointBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (auto& v : vertices) {
		add(Point(*v));
	}
}


void PointBuffer::clear()
{
	position.clear();
	color.clear();
	sizes.clear();
}



void PointBuffer::add(const Point& point)
{
	position.add(point.getPosition());
	color.add(point.getColor());
	sizes.add(point.getSize());
}

