#include "VolumeNode.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

VolumeNode::VolumeNode() :
	pos(Vector3d<float>(0, 0, 0)),
	value(0)
{}

VolumeNode::VolumeNode(const Vector3d<float>& p, const float& v) :
	pos(p),
	value(v)
{}

Vector3d<float> VolumeNode::getInterpolatedPosition(const float v, const VolumeNode& rhs) const
{
	const float scale = static_cast<float> (v - this->value) / static_cast<float>(rhs.value - this->value);
	return this->pos + scale * (rhs.pos - this->pos);
}

Particle VolumeNode::toParticle(const float radius) const
{
	return Particle(this->pos, this->value, radius);
}
