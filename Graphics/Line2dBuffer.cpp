#include "stdafx.h"
#include "Line2dBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;


Line2dBuffer::Line2dBuffer(const Line2d<float>& line, const ColorRGBA<float>& color) {
	add(line, color);
}

void Line2dBuffer::add(const Line2d<float>& line, const ColorRGBA<float>& color)
{
	position.add(line.getStart());
	position.add(line.getEnd());
	this->color.add(color);
	this->color.add(color);
	this->ids.push_back(static_cast<unsigned int>( this->ids.size() ));
	this->ids.push_back(static_cast<unsigned int>( this->ids.size() ));
}
