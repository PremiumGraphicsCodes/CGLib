#include "PointBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;

Point::Point(const Particle& particle, const unsigned int id)
{
	position = particle.getPosition();
	color = ColorRGBA<float>(1.0, 1.0, 0.0, particle.getValue());
	size = particle.getDiameter();
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

