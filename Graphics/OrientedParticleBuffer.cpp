#include "OrientedParticleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void OrientedParticleBuffer::clear()
{
	indices.clear();
	position.clear();
	texCoord.clear();
	orientation.clear();
	color.clear();
}


void OrientedParticleBuffer::add(const OrientedParticle& e)
{
	int i1 = position.get().size() / 3;
	int i2 = i1 + 1;
	int i3 = i1 + 2;
	int i4 = i1 + 3;

	position.add(e.getPosition() + Vector3d<float>(-e.getRadii().getX(), e.getRadii().getX(), 0.0));
	position.add(e.getPosition() + Vector3d<float>(-e.getRadii().getX(), -e.getRadii().getY(), 0.0));
	position.add(e.getPosition() + Vector3d<float>(e.getRadii().getX(), -e.getRadii().getY(), 0.0));
	position.add(e.getPosition() + Vector3d<float>(e.getRadii().getX(), e.getRadii().getY(), 0.0));

	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);

	indices.push_back(i1);
	indices.push_back(i3);
	indices.push_back(i4);

	texCoord.add(Vector2d<float>(-1, 1));
	texCoord.add(Vector2d<float>(-1, -1));
	texCoord.add(Vector2d<float>(1, -1));
	texCoord.add(Vector2d<float>(1, 1));


	orientation.add(e.getOrientation());
	orientation.add(e.getOrientation());
	orientation.add(e.getOrientation());
	orientation.add(e.getOrientation());

	color.add(e.getColor());
	color.add(e.getColor());
	color.add(e.getColor());
	color.add(e.getColor());
}