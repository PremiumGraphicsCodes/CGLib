#include "../Graphics/ICamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
ICamera<T>::ICamera() :
	up(Vector3d<T>(0,1,0)),
	lookat(Vector3d<T>(0,0,0))
{
}


template<typename T>
Matrix3d<T> ICamera<T>::getRotationMatrix() const
{
	Matrix3d<T> matrix = Math::Matrix3d<T>::Identity();
//	Vector3d<T> y = 
	matrix *= Math::Matrix3d<T>::RotateX(angle.getX());
	matrix *= Math::Matrix3d<T>::RotateY(angle.getY());
	matrix *= Math::Matrix3d<T>::RotateZ(angle.getZ());
	return matrix;

}

template<typename T>
Matrix4d<T> ICamera<T>::getModelviewMatrix() const {
	Matrix4d<T> matrix;
	matrix.translate(pos.getX(), pos.getY(), pos.getZ());
	matrix *= Math::Matrix4d<T>::RotateX(angle.getX());
	matrix *= Math::Matrix4d<T>::RotateY(angle.getY());
	matrix *= Math::Matrix4d<T>::RotateZ(angle.getZ());
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


template class ICamera<float>;
template class ICamera<double>;
