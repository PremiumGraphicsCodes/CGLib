#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

AnisotoropicParticle::AnisotoropicParticle(const int id)
	: IParticle(id)
{}

AnisotoropicParticle::AnisotoropicParticle(const Ellipsoid<float>& ellipsoid, const float density, const int id) :
	IParticle(ellipsoid.getCenter(),density, id),
	scale(ellipsoid.getRadii()),
	orientation(Quaternion<float>::Unit())
{
}

void AnisotoropicParticle::rotate(const Quaternion<float>& q)
{
	orientation *= q;
}

Matrix3d<float> AnisotoropicParticle::getMatrix() const
{
	return Matrix3d<float>();
}

Box3d<float> AnisotoropicParticle::getBoundingBox() const
{
	const auto minx = position.getX() - scale.getX() * 0.5f;
	const auto miny = position.getY() - scale.getY() * 0.5f;
	const auto minz = position.getZ() - scale.getZ() * 0.5f;
	const auto maxx = position.getX() + scale.getX() * 0.5f;
	const auto maxy = position.getY() + scale.getY() * 0.5f;
	const auto maxz = position.getZ() + scale.getZ() * 0.5f;
	return Box3d<float>(Vector3d<float>(minx, miny, minz), Vector3d<float>(maxx, maxy, maxz));
}

float AnisotoropicParticle::getBoundingRadius() const
{
	return std::max<float>({ scale.getX() * 0.5f, scale.getY() * 0.5f, scale.getZ() * 0.5f });
}
