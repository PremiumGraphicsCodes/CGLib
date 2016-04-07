#include "OrthogonalCamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
void OrthogonalCamera<T>::init()
{
	near_ = 1;
	far_ = 10.0;
	pos = Math::Vector3d<T>::Zero();

}

template<typename T>
Matrix4d<T> OrthogonalCamera<T>::getProjectionMatrix() const
{
	//const T left = T{ -0.5 };
	//const T right = T{ 0.5 };

	const T dx = right - left;
	const T dy = top - bottom;
	const T dz = far_ - near_;

	Math::Matrix4d<T> matrix;
	matrix.setX00(T{ 2 } / dx);
	matrix.setX11(T{ 2 } / dy);
	matrix.setX22(T{ -2 } / dz);
	matrix.setX30(-(right + left) / dx);
	matrix.setX31(-(top + bottom) / dy);
	matrix.setX32(-(far_ + near_) / dz);

	return matrix;
}

template class OrthogonalCamera<float>;
template class OrthogonalCamera<double>;
