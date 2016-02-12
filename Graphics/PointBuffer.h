#ifndef __CRYSTAL_GRAPHICS_POINT_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Polygon {
		class PointObject;
		class PolygonObject;
		class Particle;
		class ParticleObject;
		class ActorObject;
		class Joint;
		class Vertex;
	}
	namespace Graphics {

class Point
{
public:
	Point(const Math::Vector3d<float>& position, const ColorRGBA<unsigned char>& color, const float size) :
		position(position),
		color(color),
		size(size)
	{}

	Point(const Polygon::Vertex& vertex);

	Point(const Polygon::Particle& particle);

	Point(const Polygon::Joint& joint);

	Math::Vector3d<float> getPosition() const { return position; }

	ColorRGBA<unsigned char> getColor() const { return color; }

	float getSize() const { return size; }

private:
	Math::Vector3d<float> position;
	ColorRGBA<unsigned char> color;
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

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<unsigned char> getColor() const { return color; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }
	
private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<unsigned char> color;
	Graphics::Buffer1d<float> sizes;
};

	}
}

#endif