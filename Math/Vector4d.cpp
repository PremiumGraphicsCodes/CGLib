#include "Vector4d.h"
#include "Vector3d.h"

using namespace Crystal::Math;

template<typename T>
Vector4d<T>::Vector4d(const Vector3d<T>& v) :
	x(v.getX()),
	y(v.getY()),
	z(v.getZ()),
	w(1.0)
{}


template<typename T>
Vector4d<T> Vector4d<T>::getMult(const Matrix4d<T>& matrix) const
{
	const auto nx = x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20() + w * matrix.getX30();
	const auto ny = x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21() + w * matrix.getX31();
	const auto nz = x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22() + w * matrix.getX32();
	const auto nw = x * matrix.getX03() + y * matrix.getX13() + z * matrix.getX23() + w * matrix.getX33();

	return Vector4d(nx, ny, nz, nw);
}

template<typename T>
T Vector4d<T>::getDistanceSquared(const Vector4d& rhs) const
{
	return pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2) + pow(w - rhs.w, 2);
}

template<typename T>
Vector3d<T> Vector4d<T>::toVector3d() const
{
	return Vector3d<T>(x / w, y / w, z / w);
}

template<typename T>
Vector4d<T> Vector4d<T>::operator*(const Matrix4d<T>& matrix)
{
	return getMult(matrix);
}


template class Vector4d<float>;
template class Vector4d<double>;