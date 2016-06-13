#include "Vector3d.h"
#include "Matrix4d.h"
#include "PolarCoord3d.h"

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
Vector3d<T>::Vector3d(const Vector2d<T>& v, const T z) :
	x(v.getX()),
	y(v.getY()),
	z(z)
{
}


template<typename T>
Vector3d<T>::Vector3d(const std::array<T, 3>& v) :
	Vector3d(v[0], v[1], v[2])
{
}

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
bool Vector3d<T>::equals(const Vector3d<T>&rhs) const
{
	const auto tolerance = 1.0e-6f;
	return
		Tolerance<T>::isEqual(this->x, rhs.x, tolerance) &&
		Tolerance<T>::isEqual(this->y, rhs.y, tolerance) &&
		Tolerance<T>::isEqual(this->z, rhs.z, tolerance);
	//return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
}


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
Vector3d<T> Vector3d<T>::operator*(const float factor) const
{
	Vector3d vector(*this);
	return vector.scale(factor);
}

template<typename T>
Vector3d<T> Vector3d<T>::operator/(const float factor) const
{
	Vector3d vector(*this);
	return vector.scale(1.0f / factor);
}


template<typename T>
Vector3d<T> Vector3d<T>::getMult(const Matrix3d<T>& matrix) const
{
	const auto nx = x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20();
	const auto ny = x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21();
	const auto nz = x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22();
	return Vector3d(nx, ny, nz);
}

template<typename T>
T Vector3d<T>::getInnerProduct(const Vector3d& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}


template<typename T>
Vector3d<T> Vector3d<T>::getOuterProduct(const Vector3d& rhs) const
{
	return Vector3d
	(
		y * rhs.z - z * rhs.y,
		-(x * rhs.z - z * rhs.x),
		x * rhs.y - y * rhs.x
	);
}


#include "Vector4d.h"

template<typename T>
void Vector3d<T>::transform(const Matrix4d<T>& matrix)
{
	Vector4d<T> v(*this);
	v.multiple(matrix);
	*this = v.toVector3d();
}

template<typename T>
T Vector3d<T>::operator[](const int index) const
{
	assert(0 <= index  && index <= 3);
	return toArray()[index];
}

template<typename T>
Matrix3d<T> Vector3d<T>::toDiagonalMatrix() const
{
	return Matrix3d<T>(
		getX(), 0, 0,
		0, getY(), 0,
		0, 0, getZ() );
}

template<typename T>
Angle<T> Vector3d<T>::getAngle(const Vector3d<T>& rhs) const
{
	const auto inner = getInnerProduct(rhs);
	return Angle<T>( Radian<T>(std::acos(inner)) );
}


template<typename T>
PolarCoord3d<T> Vector3d<T>::toPolarCoord() const
{
	Vector3d<T> xunit(1, 0, 0);
	Vector3d<T> yunit(0, 1, 0);
	Vector3d<T> v(x, 0, z);
	
	const auto azimuth = xunit.getAngle(v);
	const auto elevation = yunit.getAngle(v);
	
	return PolarCoord3d<T>(getLength(), azimuth, elevation);
}

template<typename T>
Angle<T> Vector3d<T>::getAzimuth() const
{
	Vector3d<T> xunit(1, 0, 0);
	Vector3d<T> v(x, 0, z);
	const auto angle = xunit.getAngle(v);
	if (z >= 0) {
		return angle;
	}
	else {
		return -angle;
	}
}

template<typename T>
Angle<T> Vector3d<T>::getElevation() const
{
	Vector3d<T> yunit(0, 1, 0);
	return getAngle(yunit);
}


template class Vector3d<float>;
template class Vector3d<double>;