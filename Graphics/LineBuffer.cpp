#include "LineBuffer.h"

using namespace Crystal::Graphics;

void LineBuffer::clear()
{
	position.clear();
	color.clear();
}

void LineBuffer::add(const Line& line)
{
	position.add(line.getLine().getStart());
	position.add(line.getLine().getEnd());
	color.add(line.getColor());
	color.add(line.getColor());
}

