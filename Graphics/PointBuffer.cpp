#include "PointBuffer.h"

using namespace Crystal::Graphics;

void PointBuffer::clear()
{
	position.clear();
	color.clear();
	sizes.clear();
}


std::vector<IBuffer<float>> PointBuffer::getBuffers() const
{
	std::vector<IBuffer<float>> buffers;
	buffers.push_back(position);
	buffers.push_back(color);
	buffers.push_back(sizes);
	return buffers;
}

void PointBuffer::add(const Point& point)
{
	position.add(point.getPosition());
	color.add(point.getColor());
	sizes.add(point.getSize());
}

