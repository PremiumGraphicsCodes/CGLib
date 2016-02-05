#ifndef __CRYSTAL_GRAPHICS_POINT_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Polygon/ParticleObject.h"

namespace Crystal {
	namespace Graphics {

class Point
{
public:
	Point(const Math::Vector3d<float>& position, const ColorRGBA<float>& color, const float size, const unsigned int id) :
		position(position),
		color(color),
		size(size),
		id(id)
	{}

	Point(const Polygon::Particle& particle, const unsigned int id);

	Math::Vector3d<float> getPosition() const { return position; }

	ColorRGBA<float> getColor() const { return color; }

	float getSize() const { return size; }

	unsigned int getId() const { return id; }

private:
	Math::Vector3d<float> position;
	ColorRGBA<float> color;
	float size;
	unsigned int id;
};

struct PointBuffer
{
public:
	PointBuffer() {};

	PointBuffer(const Polygon::ParticleObject& particles);

	void clear();

	void add(const Point& point);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }
	
	std::vector<unsigned int> getIds() const { return ids; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer1d<float> sizes;
	std::vector<unsigned int> ids;
};

	}
}

#endif