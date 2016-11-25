#include "IPrimitive3d.h"

using namespace Crystal::Math;

template<typename T>
Matrix3d<T> IPrimitive3d<T>::getTranslateMatrix() const
{
	return Matrix3d<T>(
		center.getX(), 0, 0,
		0, center.getY(), 0,
		0, 0, center.getZ()
		);
}

template<typename T>
Matrix3d<T> IPrimitive3d<T>::getRotationMatrix() const
{
	return orientation.toMatrix();
}

template<typename T>
Matrix3d<T> IPrimitive3d<T>::getScalingMatrix() const
{
	return Matrix3d<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

template<typename T>
Matrix3d<T> IPrimitive3d<T>::getMatrix() const
{
	return getScalingMatrix() * getRotationMatrix() * getTranslateMatrix();
}

template class IPrimitive3d<float>;
template class IPrimitive3d<double>;