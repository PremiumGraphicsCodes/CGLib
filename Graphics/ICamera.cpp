#include "../Graphics/ICamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
Matrix3d<T> ICamera<T>::getRotationMatrix() const
{
	Matrix3d<T> matrix = Math::Matrix3d<T>::Identity();
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


template class ICamera<float>;
template class ICamera<double>;
