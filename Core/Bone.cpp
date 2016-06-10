#include "Bone.h"

#include "Joint.h"

#include "../Math/Line3d.h"
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

std::vector<AnisotoropicParticle> Bone::toAnisoParticles(const float divideLength, const float density)
{
	std::vector<AnisotoropicParticle> particles;

	const auto& ellipsoids = toEllipsoids(divideLength);
	for (const auto& e : ellipsoids) {
		AnisotoropicParticle ap(e, density, e.getOrientation());
		particles.emplace_back(ap);
	}

	return particles;
}

std::vector< Ellipsoid<float> > Bone::toEllipsoids(const float divideLength) const
{
	std::vector< Ellipsoid<float> > results;

	const auto length = this->getLength();
	const float start = origin->getBoundingRadius() + divideLength * 0.5f;
	const float end = length - dest->getBoundingRadius();// - divideLength * 0.5f;
	const auto vector = dest->getPosition() - origin->getPosition();
	PolarCoord3d<float> polar(vector);
	const auto& orientation = polar.toQuaternion();
	//const auto& orientation = polar.toQuaternion();
	for (float l = start; l < end; l += divideLength) {
		const float ratio = l / length;
		const auto pos = getOriginJoint()->getPosition() * (1.0f - ratio) + getDestJoint()->getPosition() * (ratio);
		const Vector3d<float> radii(divideLength, thickness.getX(), thickness.getY());
		const Ellipsoid<float> e(pos, radii, orientation);
		results.push_back(e);
	}
	return results;
}



void Bone::move(const Vector3d<float>& v)
{
	origin->move(v);
	dest->move(v);
}