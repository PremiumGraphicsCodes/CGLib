#include "OrientedParticleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void OrientedParticleBuffer::clear()
{
	position.clear();
	radii.clear();
	orientation.clear();
	color.clear();
}


void OrientedParticleBuffer::add(const OrientedParticle& e)
{
	position.add(e.getPosition());
	radii.add(e.getRadii());
	orientation.add(e.getOrientation());
	color.add(e.getColor());
}