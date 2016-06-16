#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"
#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Bone::Bone(Joint* origin, Joint* dest, const Vector3d<float>& thickness, const unsigned int id) :
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
	auto b = new Bone(dest, childDest, Vector3d<float>(1,1,1), 1);
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

std::vector<AnisotoropicParticle> Bone::toAnisoParticles(const float density, const float divideLength)
{
	std::vector<AnisotoropicParticle> particles;

	const auto& ellipsoids = toEllipsoids(divideLength);
	for (const auto& e : ellipsoids) {
		AnisotoropicParticle ap(e, density, e.getOrientation());
		particles.emplace_back(ap);
	}

	return particles;
}

PolarCoord3d<float> Bone::getPolarCoord() const
{
	const auto vector = dest->getPosition() - origin->getPosition();
	return vector.toPolarCoord();
}


Quaternion<float> Bone::getOrientation() const
{
	return getPolarCoord().getOrientation();
}


std::vector< Ellipsoid<float> > Bone::toEllipsoids(const float divideLength) const
{
	std::vector< Ellipsoid<float> > results;

	const auto length = this->getLength();
	const auto& orientation = getOrientation();
	for (float l = 0.0f; l < length; l += divideLength) {
		const float ratio = l / length;
		const auto pos = getOriginJoint()->getPosition() * (1.0f - ratio) + getDestJoint()->getPosition() * (ratio);
		const Vector3d<float> radii(thickness.getX(), thickness.getY(), thickness.getZ());
		const Ellipsoid<float> e(pos, radii, orientation);
		results.push_back(e);
	}
	return results;
}

#include "../Math/Cylindroid.h"

Cylindroid<float> Bone::toCylindroid() const
{
	const auto polarCoord = getPolarCoord();
	PolarCoord3d<float> pc(polarCoord.getLength(), polarCoord.getAzimuth(), polarCoord.getElevation());
	const auto center = origin->getPosition() * 0.5 + dest->getPosition() * 0.5;
	const Vector2d<float> radii(thickness.getY(), thickness.getZ());
//	Quaternion<float> q1(Vector3d<float>(1, 0, 0), Tolerance<float>::getHalfPI());
//	Quaternion<float> q2(Vector3d<float>(0, -1, 0), Tolerance<float>::getHalfPI());
//	Quaternion<float> q3(Vector3d<float>(0, 0, 1), Tolerance<float>::getHalfPI());
	Cylindroid<float> cylindroid(center,radii, getLength(), pc.getOrientation());
//	cylindroid.rotate(getOrientation());
	return cylindroid;
}


void Bone::move(const Vector3d<float>& v)
{
	origin->move(v);
	dest->move(v);
}