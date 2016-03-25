#include "PointBuffer.h"
#include "../Physics/SPHParticle.h"
#include "../Physics/PhysicsObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"
#include "../Polygon/Particle.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/VolumeObject.h"
#include "../Polygon/Joint.h"

#include <memory>

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;

Point::Point(const Crystal::Polygon::Particle& particle)
{
	position = particle.getPosition();
	color = ColorRGBA<float>(0, 0, 1.0, particle.getDensity());
	//idColor = ColorRGBA<unsigned char>(particle.getId());
	size = particle.getDiameter();
}

Point::Point(const Crystal::Physics::SPHParticle& particle)
{
	position = particle.getPosition();
	color = ColorRGBA<float>(0.0, 0.0, 1.0, particle.getDensityRatio() / 10.0f);
	size = particle.getDiameter();
}


Point::Point(const Vertex& vertex)
{
	position = vertex.getPosition();
	color = ColorRGBA<float>(vertex.getId());
	idColor = ColorRGBA<unsigned char>(vertex.getId());
	size = 1.0f;
}


Point::Point(const Joint& joint)
{
	position = joint.getPosition();
	color = ColorRGBA<float>(1.0, 1.0, 1.0, 1.0f);
	//idColor = ColorRGBA<unsigned char>(joing.getId());

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

void PointBuffer::add(const VolumeObject& volume)
{
	const auto& particles = volume.toParticles(0.1f, 0.1f);
	for (const auto& p : particles) {
		add(p);
	}
}


void PointBuffer::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (auto& v : vertices) {
		add(Point(*v));
	}
}

void PointBuffer::add(const PhysicsObject& physics)
{
	const auto& particles = physics.getParticles();
	for (auto& p : particles) {
		add(Point(*p));
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
	idColor.add(point.getIdColor());
	sizes.add(point.getSize());
}

