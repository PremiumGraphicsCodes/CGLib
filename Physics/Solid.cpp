#include "Solid.h"

#include "../Math/Box.h"
#include "../Math/Quaternion.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

btVector3 Converter::convert(const Vector3d<float>& src)
{
	return btVector3(src.getX(), src.getY(), src.getZ());
}

Vector3d<float> Converter::convert(const btVector3& src)
{
	return Vector3d<float>(src.getX(), src.getY(), src.getZ());
}

Quaternion<float> Converter::convert(const btQuaternion& src)
{
	return Quaternion<float>( src.getX(), src.getY(), src.getZ(), src.getW());
}

Surfels::Surfels(const Box<float>& box, const float divideLength)
{
	const auto minx = box.getMinX();
	const auto miny = box.getMinY();
	const auto minz = box.getMinZ();
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();
	for (auto y = miny; y < maxy; y += divideLength) {
		for (auto z = minz; z < maxz; z += divideLength) {			
			positions.push_back(Vector3d<float>(minx, y, z));
			positions.push_back(Vector3d<float>(maxx, y, z));
		}
	}
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto y = miny; y < maxy; y += divideLength) {
			positions.push_back(Vector3d<float>(x, y, minz));
			positions.push_back(Vector3d<float>(x, y, maxz));
		}
	}
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto z = miny; z < maxz; z += divideLength) {
			positions.push_back(Vector3d<float>(x, miny, z));
			positions.push_back(Vector3d<float>(x, maxy, z));
		}
	}
}

std::vector<Vector3d<float>> Surfels::getWorld(const Vector3d<float>& center, const Quaternion<float>& rotation) const
{
	std::vector<Vector3d<float>> result;
	const auto& matrix = rotation.toMatrix();
	for (const auto& p : positions) {
		auto pos = p * matrix;
		pos += center;
	}
	return result;
}



Solid::Solid(const Box<float>& box, const float mass)
{
	const auto length = box.getLength() * 0.5;
	auto shape = new btBoxShape( Converter::convert(length) );

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( Converter::convert(box.getMin() ) );

	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
	body = new btRigidBody(info);

	//box.getMin
};

Solid::Solid(const Sphere<float>& sphere, const float mass)
{
	const auto center = sphere.getCenter();
	const auto originx = center.getX() - sphere.getRadius();
	const auto originy = center.getY() - sphere.getRadius();
	const auto originz = center.getZ() - sphere.getRadius();

	auto shape = new btSphereShape(sphere.getRadius());

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(originx, originy, originz));
}

float Solid::getMass() const
{
	return 1.0f / (body->getInvMass());
}

bool Solid::isDynamic() const
{
	return getMass() != 0.0f;
}

bool Solid::isStatic() const
{
	return getMass() == 0.0f;
}

Vector3d<float> Solid::getOrigin() const
{
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	return Converter::convert( transform.getOrigin() );
}

Quaternion<float> Solid::getOrientation() const
{
	return Converter::convert(body->getOrientation());
}

//Mat