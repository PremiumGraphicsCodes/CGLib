#include "EllipsoidBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void EllipsoidBuffer::add(const Ellipsoid& e)
{
	position.add( e.getPosition() );
	size.add(e.getSize());
}