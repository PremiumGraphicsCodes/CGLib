#include "stdafx.h"
#include "Bone.h"

#include "Joint.h"

#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Bone::Bone(Joint* origin, Joint* dest, const Vector2d<float>& thickness, const unsigned int id) :
	origin(origin),
	dest(dest),
	thickness(thickness),
	id(id)
{}

Bone::~Bone()
{
	clear();
}

Bone* Bone::clone(const unsigned int newId) const
{
	return new Bone(origin, dest, thickness, newId);
}

void Bone::clear()
{
	for (auto c : children) {
		delete c;
	}
	children.clear();
}


Bone* Bone::createChild(Joint* childDest)
{
	auto b = new Bone(dest, childDest, Vector2d<float>(1,1), 1);
	children.push_back(b);
	return b;
}

float Bone::getLength() const
{
	return toLine().getLength();
}

Line3d<float> Bone::toLine() const
{
	return Line3d<float>(origin->getPosition(), dest->getPosition());
}


#include "../Math/PolarCoord3d.h"

AnisotoropicParticle Bone::toAnisoParticles(const float density)
{
	const auto& e = toEllipsoid();
	return AnisotoropicParticle(e, density, e.getOrientation());
}

PolarCoord3d<float> Bone::getPolarCoord() const
{
	const auto vector = dest->getPosition() - origin->getPosition();
	return vector.toPolarCoord();
}


Quaternion<float> Bone::getOrientation() const
{
	const Quaternion<float> q(Vector3d<float>(1, 0, 0), rotation.getRadian().get());
	return getPolarCoord().getOrientation() * q;
}


Ellipsoid<float> Bone::toEllipsoid() const
{
	std::vector< Ellipsoid<float> > results;

	const auto length = this->getLength();
	const auto& orientation = getOrientation();
	const auto pos = getCenter();
	const Vector3d<float> radii(length*0.5f, thickness.getX(), thickness.getY());	
	return Ellipsoid<float>(pos, radii, orientation);
}

#include "../Math/Cylindroid.h"

Cylindroid<float> Bone::toCylindroid() const
{
	Cylindroid<float> cylindroid(getCenter(), thickness, getLength(), getOrientation());
	return cylindroid;
}

Vector3d<float> Bone::getCenter() const
{
	return origin->getPosition() * 0.5 + dest->getPosition() * 0.5;
}


void Bone::move(const Vector3d<float>& v)
{
	origin->move(v);
	dest->move(v);
}