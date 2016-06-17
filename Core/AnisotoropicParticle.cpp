#include "stdafx.h"
#include "AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

AnisotoropicParticle::AnisotoropicParticle(const int id)
	: IParticle(id),
	radii(0.5f, 0.5f, 0.5f)
{}

AnisotoropicParticle::AnisotoropicParticle(const Ellipsoid<float>& ellipsoid, const float density, const int id) :
	IParticle(ellipsoid.getCenter(),density, id),
	radii(ellipsoid.getRadii()),
	orientation(ellipsoid.getOrientation())
{
}

AnisotoropicParticle::AnisotoropicParticle(const Ellipsoid<float>& ellipsoid, const float density, const Quaternion<float>& orientation, const int id) :
	IParticle(ellipsoid.getCenter(),density, id),
	radii(ellipsoid.getRadii()),
	orientation(orientation)
{
}

void AnisotoropicParticle::rotate(const Quaternion<float>& q)
{
	orientation *= q;
}

Box3d<float> AnisotoropicParticle::getBoundingBox() const
{
	const auto& matrix = getMatrix();
	const auto x11 = matrix.getX00();
	const auto x12 = matrix.getX01();
	const auto x13 = matrix.getX02();

	const auto x21 = matrix.getX10();
	const auto x22 = matrix.getX11();
	const auto x23 = matrix.getX12();

	const auto x31 = matrix.getX20();
	const auto x32 = matrix.getX21();
	const auto x33 = matrix.getX22();


	const auto x = std::sqrt(x11*x11 + x12*x12 + x13*x13);
	const auto y = std::sqrt(x21*x21 + x22*x22 + x23*x23);
	const auto z = std::sqrt(x31*x31 + x32*x32 + x33*x33);
	//const auto y1 = Vector3d<float>(x1, x1, x1);
	//const auto v2 = v1;
	const Vector3d<float> v1(x, y, z);
	const Vector3d<float> v2(-x,-y,-z);
	return Box3d<float>(v1 + getPosition(),v2 + getPosition());
}

float AnisotoropicParticle::getBoundingRadius() const
{
	return std::max<float>({ radii.getX(), radii.getY(), radii.getZ() });
}

Matrix3d<float> AnisotoropicParticle::getScalingMatrix() const
{
	return Matrix3d<float>(
		radii.getX(), 0, 0,
		0, radii.getY(), 0,
		0, 0, radii.getZ());
}

Matrix3d<float> AnisotoropicParticle::getRotationMatrix() const
{
	return orientation.toMatrix();
}

Matrix3d<float> AnisotoropicParticle::getMatrix() const
{
	const auto& rotation = getRotationMatrix();
	const auto& scaling = getScalingMatrix();
	const auto& invRotation = rotation.transposed();
	return rotation * scaling * invRotation;
}

void AnisotoropicParticle::scale(const Vector3d<float>& s)
{
	radii.setX(radii.getX() * s.getX());
	radii.setY(radii.getY() * s.getY());
	radii.setZ(radii.getZ() * s.getZ());
}


AnisotoropicParticle* AnisotoropicParticle::clone(const int newId) const
{
	Ellipsoid<float> e(this->getPosition(), radii);
	return new AnisotoropicParticle(e, density, orientation, newId);
}
