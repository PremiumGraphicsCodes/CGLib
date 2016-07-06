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
Vector3d<T> Vector3d<T>::normalized() const
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
Vector3d<T> Vector3d<T>::operator*(const T factor) const
{
	Vector3d vector(*this);
	return vector.scale(factor);
}

template<typename T>
Vector3d<T> Vector3d<T>::operator/(const T factor) const
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
	/*
	const auto s = getOuterProduct(rhs).getLength();
	const auto c = getInnerProduct(rhs);
	return Angle<T>( Radian<T>(std::atan2(s, c)) );
	*/
}

template<typename T>
Angle<T> Vector3d<T>::getSingedAngle(const Vector3d<T>& rhs, const Vector3d<T>& normal) const
{
	const auto angle = getAngle(rhs);
	return isLeft(rhs, normal) ? angle : -angle;
}


template<typename T>
PolarCoord3d<T> Vector3d<T>::toPolarCoord() const
{
	return PolarCoord3d<T>(getLength(), getAzimuth(), getElevation());
}

template<typename T>
Angle<T> Vector3d<T>::getAzimuth() const
{
	//Vector3d<T> v = getNormalized();
	//Vector3d<T> xaxis(1, 0, 0);
	Vector2d<T> xz(x, z);
	if (xz == Vector2d<T>(0, 0)) {
		return Angle<T>::Zero();
	}
	xz.normalize();
	return -xz.getAngle();
	//xz.getAngle();
	//auto theta = Angle<T>(Radian<T>(std::acos(z / getLength())));
	//theta = theta - Angle<T>(Radian<T>(Tolerance<T>::getHalfPI()));
	//return xaxis.getSingedAngle(xz, Vector3d<T>(0, 1, 0));
}

template<typename T>
Angle<T> Vector3d<T>::getElevation() const
{
	const auto& n = normalized();
	return -(n.getAngle(Vector3d<T>(0,1,0)) - Angle<T>(Degree<T>(90)));
}

template<typename T>
bool Vector3d<T>::isLeft(const Vector3d<T>& rhs, const Vector3d<T>& normal) const
{
	const auto& cross = getOuterProduct(rhs);
	return normal.getInnerProduct(cross) > 0;
}

#include "PolarCoord3d.h"

template<typename T>
Vector3d<T> Vector3d<T>::lerp(const Vector3d& rhs, const T param) const
{
	const auto xx = this->x * (1 - param) + rhs.x * param;
	const auto yy = this->y * (1 - param) + rhs.y * param;
	const auto zz = this->z * (1 - param) + rhs.z * param;
	return Vector3d<T>(xx, yy, zz);
}


template<typename T>
Vector3d<T> Vector3d<T>::slerp(const Vector3d<T>& rhs, const T param) const
{
	const auto q1 = toPolarCoord().getOrientation();
	const auto q2 = rhs.toPolarCoord().getOrientation();

	Quaternion<T> qq = q1.slerp(q2, param);
	const auto result = Vector3d<T>(1,0,0).getMult(qq.toMatrix().transposed());
	return result;
}

template<typename T>
bool Vector3d<T>::isSamePlane(const Vector3d<T>& a, const Vector3d<T>& b, const Vector3d<T>& c) const
{
	const auto& v0 = a - *this;
	const auto& v1 = b - *this;
	const auto& v2 = c - *this;
	const Matrix3d<T> matrix(
		v0.getX(), v0.getY(), v0.getZ(),
		v1.getX(), v1.getY(), v1.getZ(),
		v2.getX(), v2.getY(), v2.getZ()
	);
	return Tolerance<T>::isEqualLoosely(matrix.getDeterminant(), 0);
}


template class Vector3d<float>;
template class Vector3d<double>;