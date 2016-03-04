#ifndef __CRYSTAL_GRAPHICS_POINT_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Physics {
		class Particle;
		class PhysicsObject;
	}
	namespace Polygon {
		class PointObject;
		class PolygonObject;
		class Particle;
		class ParticleObject;
		class VolumeObject;
		class ActorObject;
		class Joint;
		class Vertex;
	}
	namespace Graphics {

class Point
{
public:
	/*
	Point(const Math::Vector3d<float>& position, const ColorRGBA<unsigned char>& color, const float size) :
		position(position),
		color(color),
		size(size)
	{}
	*/

	Point(const Polygon::Vertex& vertex);

	Point(const Polygon::Particle& particle);

	Point(const Physics::Particle& particle);

	Point(const Polygon::Joint& joint);

	Math::Vector3d<float> getPosition() const { return position; }

	ColorRGBA<float> getColor() const { return color; }

	ColorRGBA<unsigned char> getIdColor() const { return idColor; }

	float getSize() const { return size; }

private:
	Math::Vector3d<float> position;
	ColorRGBA<float> color;
	ColorRGBA<unsigned char> idColor;
	float size;
};

class PointBuffer
{
public:
	PointBuffer() {};

	PointBuffer(const Polygon::ParticleObject& particles);

	void clear();

	void add(const Point& point);

	void add(const Polygon::ParticleObject& object);

	void add(const Polygon::ActorObject& actor);

	void add(const Polygon::PolygonObject& polygon);

	void add(const Polygon::VolumeObject& volume);

	void add(const Physics::PhysicsObject& physics);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Graphics::Buffer4d<unsigned char> getIdColor() const { return idColor; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }
	
private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer4d<unsigned char> idColor;
	Graphics::Buffer1d<float> sizes;
};

	}
}

#endif