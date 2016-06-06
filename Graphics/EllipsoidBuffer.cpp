#include "EllipsoidBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void EllipsoidBuffer::add(const Ellipsoid& e)
{
	position.add( e.getPosition() );
	size.add(e.getSize());
	matrixRow1.add(e.getMatrix().getRowVector(0));
	matrixRow2.add(e.getMatrix().getRowVector(1));
	matrixRow3.add(e.getMatrix().getRowVector(2));
	color.add(e.getColor());
}