#include "Vector3d.h"
#include "Matrix4d.h"

using namespace Crystal::Math;

template<typename T>
Vector3d<T>::Vector3d(void) :
	Vector3d(0, 0, 0)
{}

template<typename T>
Vector3d<T>::Vector3d(const Vector2d<T>& v) :
	x(v.getX()),
	y(v.getY()),
	z(0)
{}

template<typename T>
Vector3d<T>::Vector3d(const T x, const T y, const T z) :
	x(x), y(y), z(z)
{}

template<typename T>
Vector3d<T>::Vector3d(const Vector3d& start, const Vector3d& end) :
	x(end.x - start.x),
	y(end.y - start.y),
	z(end.z - start.z)
{}


template<typename T>
Vector3d<T>& Vector3d<T>::scale(const T factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

template<typename T>
Vector3d<T>& Vector3d<T>::scale(const T xFactor, const T yFactor, const T zFactor)
{
	x *= xFactor;
	y *= yFactor;
	z *= zFactor;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::normalize()
{
	const auto length = getLength();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::getNormalized() const
{
	Vector3d<T> vector = *(this);
	return vector.normalize();
}

template<typename T>
Vector3d<T> Vector3d<T>::operator+=(const Vector3d& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::operator-=(const Vector3d& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template<typename T>
Vector3d<T> Vector3d<T>::getMult(const Matrix3d<T>& matrix) const
{
	const auto nx = x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20();
	const auto ny = x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21();
	const auto nz = x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22();
	return Vector3d(nx, ny, nz);
}

#include "Vector4d.h"

template<typename T>
void Vector3d<T>::transform(const Matrix4d<T>& matrix)
{
	Vector4d<T> v(*this);
	v.multiple(matrix);
	*this = v.toVector3d();
}


template class Vector3d<float>;
template class Vector3d<double>;