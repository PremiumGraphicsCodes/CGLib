#include "stdafx.h"
#include "PointBuffer.h"
#include "../Physics/SPHParticle.h"
#include "../Physics/PhysicsObject.h"

#include "DrawableID.h"

#include <memory>

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Core;

Point::Point(const Crystal::Core::Particle& particle)
{
	position = particle.getPosition();
	color = ColorRGBA<float>(0, 0, 1.0, particle.getDensity());
	idColor = DrawableID(particle.getId()).toColor();
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
	color = ColorRGBA<float>(0.0, 0.0, 1.0, 1.0f);//ColorRGBA<float>(vertex.getId());
	//idColor = ColorRGBA<unsigned char>(vertex.getId());
	size = 1.0f;
}



void PointBuffer::add(const Volume& volume)
{
	const auto& particles = volume.toParticles(0.1f, 0.1f);
	for (const auto& p : particles) {
		add(p);
	}
}


void PointBuffer::add(const PolygonMesh& polygon)
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
	idColor.clear();
	sizes.clear();
}



void PointBuffer::add(const Point& point)
{
	position.add(point.getPosition());
	color.add(point.getColor());
	idColor.add(point.getIdColor());
	sizes.add(point.getSize());
}

