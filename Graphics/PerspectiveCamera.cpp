#include "PerspectiveCamera.h"

#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

template<typename T>
void PerspectiveCamera<T>::init()
{
	near_ = 1;
	far_ = 10.0;
	pos = Math::Vector3d<T>::Zero();
}

template<typename T>
Matrix4d<T> PerspectiveCamera<T>::getProjectionMatrix() const
{
	const auto x00 = 2 * near_ / (right - left);
	const auto x02 = (right + left) / (right - left);
	const auto x11 = 2 * near_ / (top - bottom);
	const auto x12 = (top + bottom) / (top - bottom);
	const auto x22 = -(far_ + near_) / (far_ - near_);
	const auto x23 = -2 * far_ * near_ / (far_ - near_);
	return Matrix4d<T>
		(
			x00, 0, x02, 0,
			0, x11, x12, 0,
			0, 0, x22, x23,
			0, 0, -1, 0
			).transposed();
}

template class PerspectiveCamera<float>;
template class PerspectiveCamera<double>;
