#include "PerspectiveCamera.h"

#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
void PerspectiveCamera<T>::init()
{
	near_ = 1;
	far_ = 10.0;
	aspect = 1.0;
	angle = Math::Vector3d<T>::Zero();
	pos = Math::Vector3d<T>::Zero();
	fovy = Tolerance<T>::getHalfPI();
}

template<typename T>
Matrix4d<T> PerspectiveCamera<T>::getProjectionMatrix() const
{
	const auto tanHalfFovy = std::tan(fovy / T{ 2 });

	Matrix4d<T> matrix;
	matrix.setX00(1 / (aspect * tanHalfFovy));
	matrix.setX11(1 / tanHalfFovy);
	matrix.setX22(-(far_ + near_) / (far_ - near_));
	matrix.setX23((-2 * far_ * near_) / (far_ - near_));
	matrix.setX32(-1);
	matrix.setX33(0);
	return matrix;
}

template class PerspectiveCamera<float>;
template class PerspectiveCamera<double>;
