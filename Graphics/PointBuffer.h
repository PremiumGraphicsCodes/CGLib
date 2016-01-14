#ifndef __CRYSTAL_GRAPHICS_POINT_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Graphics {

class Point
{
public:
	Point(const Math::Vector3d<float>& position, const ColorRGBA<float>& color, const float size) :
		position(position),
		color(color),
		size(size)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	ColorRGBA<float> getColor() const { return color; }

	float getSize() const { return size; }
	

private:
	Math::Vector3d<float> position;
	ColorRGBA<float> color;
	float size;
};

struct PointBuffer
{
	void clear();

	void add(const Point& point);

	std::vector<IBuffer<float>> getBuffers() const;

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer1d<float> sizes;
};

	}
}

#endif