#include "Matrix2d.h"

using namespace Crystal::Math;

template<typename T>
Matrix2d<T>::Matrix2d(void) :
	Matrix2d(1, 0, 0, 1)
{
}

template<typename T>
Matrix2d<T>::Matrix2d( const T x00, const T x01, const T x10, const T x11 )
{
	x[0] = x00; x[1] = x01;
	x[2] = x10; x[3] = x11;
}

template<typename T>
void Matrix2d<T>::setIdentity()
{
	x[0] = 1;
	x[1] = 0;
	x[2] = 0;
	x[3] = 1;
}

template<typename T>
Angle<T> Matrix2d<T>::getRotationAngle() const
{
	return Angle<T>(Radian<T>(std::acos(x[0])));
}

template<typename T>
bool Matrix2d<T>::isRotation() const
{
	const auto& angle00 =  std::acos(getX00());
	const auto& angle01 = -std::asin(getX01());
	const auto& angle10 =  std::asin(getX10());
	const auto& angle11 =  std::acos(getX11());
	return (angle00 == angle01) && (angle10 == angle11);
}


template<typename T>
Matrix2d<T> Matrix2d<T>::scale(const T factor)
{
	for (auto i = 0; i < 4; ++i) {
		x[i] *= factor;
	}
	return *this;
}

template<typename T>
Matrix2d<T> Matrix2d<T>::getScaled(const T factor) const
{
	Matrix2d matrix = *this;
	return matrix.scale(factor);
}


template<typename T>
void Matrix2d<T>::setRotate(const T angle)
{
	x[0] = ::cos(angle);
	x[1] = -::sin(angle);
	x[2] = ::sin(angle);
	x[3] = ::cos(angle);
}

template<typename T>
bool Matrix2d<T>::equals(const Matrix2d& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(x[0], rhs.x[0]) &&
		Tolerance<T>::isEqualLoosely(x[1], rhs.x[1]) &&
		Tolerance<T>::isEqualLoosely(x[2], rhs.x[2]) &&
		Tolerance<T>::isEqualLoosely(x[3], rhs.x[3]);
}

template<typename T>
bool Matrix2d<T>::hasInverse() const
{
	const T denominator = getDeterminant();
	return !Tolerance<T>::isEqualStrictly(denominator, 0.0);
}

template<typename T>
Matrix2d<T> Matrix2d<T>::getInverse() const
{
	assert(hasInverse());
	const T denominator = getDeterminant();
	//assert( !Tolerancef::isEqualStrictly( denominator ) );

	const T xx00 = getX11() / denominator;
	const T xx01 = -getX01() / denominator;
	const T xx10 = -getX10() / denominator;
	const T xx11 = getX00() / denominator;

	return Matrix2d(xx00, xx01, xx10, xx11);
}

template<typename T>
Matrix2d<T> Matrix2d<T>::getProduct(const Matrix2d<T>& rhs) const
{
	return Matrix2d<T>
		(
			getX00() * rhs.getX00() + getX01() * rhs.getX10(),
			getX00() * rhs.getX01() + getX01() * rhs.getX11(),
			getX10() * rhs.getX00() + getX11() * rhs.getX10(),
			getX10() * rhs.getX01() + getX11() * rhs.getX11()
		);
}

template<typename T>
std::array<T,2> Matrix2d<T>::getEigenValues() const
{
	const auto b = getX11() + getX00();
	auto det = b*b - 4 * (getX11() * getX00() - getX01()*getX10());

	if (det < 0) {
		det = 0;
	}
	const auto eig1 = (b + sqrt(det)) / 2;
	const auto eig2 = (b - sqrt(det)) / 2;
	if (eig1 < eig2) {
		return{ eig1, eig2 };
	}
	else {
		return{ eig2, eig1 };
	}
}


template class Matrix2d<float>;
template class Matrix2d<double>;