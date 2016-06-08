#include "../Graphics/ICamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
ICamera<T>::ICamera() :
	up(Vector3d<T>(0,1,0)),
	lookat(Vector3d<T>(0,0,0))
{
	near_ = 1.0f;
	far_ = 10.0f;
	left = T{ -0.5 };
	right = T{ 0.5 };
	bottom = T{ -0.5 };
	top = T{ 0.5 };
}


template<typename T>
Matrix3d<T> ICamera<T>::getRotationMatrix() const
{
	const auto z = Vector3d<T>(pos - lookat).getNormalized();
	const auto x = getUpVector().getOuterProduct(z).getNormalized();
	const auto y = z.getOuterProduct(x);
/*	return Matrix3d<T>(
		x.getX(), x.getY(), x.getZ(),
		y.getX(), y.getY(), y.getZ(),
		z.getX(), z.getY(), z.getZ());*/
	return Matrix3d<T>(
		x.getX(), y.getX(), z.getX(),
		x.getY(), y.getY(), z.getY(),
		x.getZ(), y.getZ(), z.getZ());
}

template<typename T>
Matrix4d<T> ICamera<T>::getModelviewMatrix() const {
	Matrix4d<T> matrix( getRotationMatrix() );
	matrix.translate(-pos.getX(), -pos.getY(), -pos.getZ());
	return matrix;
}

template<typename T>
T ICamera<T>::getDistance(const T depth) const
{
	const auto dist = far_ - near_;
	return (dist * depth) + near_;
}

template<typename T>
Vector3d<T> ICamera<T>::getForwardVector() const
{
	const auto v = lookat - pos;
	return v.getNormalized();
}

template<typename T>
Vector3d<T> ICamera<T>::getUpVector() const
{
	return up.getNormalized();
}

template<typename T>
Vector3d<T> ICamera<T>::getRightVector() const
{
	return getForwardVector().getOuterProduct(getUpVector());
}

template<typename T>
Matrix4d<T> ICamera<T>::getBillboardMatrix() const
{
	auto m = getModelviewMatrix();
	Vector3d<T> z( -m[12], -m[13], -m[14]);
	z.normalize();
	Vector3d<T> x(-m[14], 0, m[12]);
	x.normalize();
	Vector3d<T> y = z.getOuterProduct(x);
	m.setX00(x.getX());
	m.setX10(x.getY());
	m.setX20(x.getZ());
	m.setX01(y.getX());
	m.setX11(y.getY());
	m.setX12(y.getZ());
	m.setX02(z.getX());
	m.setX12(z.getY());
	m.setX22(z.getZ());
	return m;
}


template class ICamera<float>;
template class ICamera<double>;
