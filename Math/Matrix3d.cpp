#include "Matrix3d.h"

#include "Vector3d.h"

using namespace Crystal::Math;

template<typename T>
Matrix3d<T>::Matrix3d(void) :
	x00(1), x01(0), x02(0),
	x10(0), x11(1), x12(0),
	x20(0), x21(0), x22(1)
{}

template<typename T>
Matrix3d<T>::Matrix3d(
	const T x00, const T x01, const T x02,
	const T x10, const T x11, const T x12,
	const T x20, const T x21, const T x22
	) :
	x00(x00), x01(x01), x02(x02),
	x10(x10), x11(x11), x12(x12),
	x20(x20), x21(x21), x22(x22)
{
}

template<typename T>
Matrix3d<T>::Matrix3d(const std::array<T, 9>& v) :
	Matrix3d(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8])
{
}


template<typename T>
bool Matrix3d<T>::equals(const Matrix3d<T>& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(x00, rhs.x00) &&
		Tolerance<T>::isEqualLoosely(x01, rhs.x01) &&
		Tolerance<T>::isEqualLoosely(x02, rhs.x02) &&
		Tolerance<T>::isEqualLoosely(x10, rhs.x10) &&
		Tolerance<T>::isEqualLoosely(x11, rhs.x11) &&
		Tolerance<T>::isEqualLoosely(x12, rhs.x12) &&
		Tolerance<T>::isEqualLoosely(x20, rhs.x20) &&
		Tolerance<T>::isEqualLoosely(x21, rhs.x21) &&
		Tolerance<T>::isEqualLoosely(x22, rhs.x22);
}

template<typename T>
T Matrix3d<T>::getDeterminant() const
{
	return
		x00 * x11 * x22
		+ x02 * x10 * x21
		+ x20 * x01 * x12
		- x02 * x11 * x20
		- x00 * x12 * x21
		- x01 * x10 * x22;
}

template<typename T>
bool Matrix3d<T>::isRegular() const
{
	const T denominator = getDeterminant();
	return !Tolerance<T>::isEqualStrictly(denominator, 0);
}

template<typename T>
Matrix3d<T> Matrix3d<T>::getInverse() const
{
	assert(isRegular());
	const T denominator = getDeterminant();

	const T i00 = x11 * x22 - x12 * x21;
	const T i01 = x21 * x02 - x22 * x01;
	const T i02 = x01 * x12 - x02 * x11;

	const T i10 = x12 * x20 - x10 * x22;
	const T i11 = x22 * x00 - x20 * x02;
	const T i12 = x02 * x10 - x00 * x12;

	const T i20 = x10 * x21 - x11 * x20;
	const T i21 = x20 * x01 - x21 * x00;
	const T i22 = x00 * x11 - x01 * x10;

	Matrix3d matrix(
		i00, i01, i02,
		i10, i11, i12,
		i20, i21, i22);
	matrix.scale(T{ 1 } / denominator);
	return matrix;
}

template<typename T>
Matrix3d<T> Matrix3d<T>::getProduct(const Matrix3d& rhs) const
{
	return Matrix3d(
		x00 * rhs.x00 + x01 * rhs.x10 + x02 * rhs.x20,
		x00 * rhs.x01 + x01 * rhs.x11 + x02 * rhs.x21,
		x00 * rhs.x02 + x01 * rhs.x12 + x02 * rhs.x22,
		x10 * rhs.x00 + x11 * rhs.x10 + x12 * rhs.x20,
		x10 * rhs.x01 + x11 * rhs.x11 + x12 * rhs.x21,
		x10 * rhs.x02 + x11 * rhs.x12 + x12 * rhs.x22,
		x20 * rhs.x00 + x21 * rhs.x10 + x22 * rhs.x20,
		x20 * rhs.x01 + x21 * rhs.x11 + x22 * rhs.x21,
		x20 * rhs.x02 + x21 * rhs.x12 + x22 * rhs.x22);
}

template<typename T>
T Matrix3d<T>::get(const int i, const int j) const
{
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);
	return toArray3x3()[i * 3 + j];
}

template<typename T>
void Matrix3d<T>::set(const int i, const int j, const T value)
{
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);
	auto arr = toArray3x3();
	arr[i + 3 + j] = value;
	*this = Matrix3d<T>(arr);
}

template<typename T>
std::array<T, 9> Matrix3d<T>::toArray3x3() const
{
	return{ x00, x01, x02, x10, x11, x12, x20, x21, x22 };
}


template<typename T>
std::vector< T > Matrix3d<T>::toArray4x4() const
{
	return{
		x00, x01, x02, 0.0f,
		x10, x11, x12, 0.0f,
		x20, x21, x22, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

template<typename T>
Matrix3d<T> Matrix3d<T>::add(const Matrix3d<T>& rhs)
{
	x00 += rhs.x00;
	x01 += rhs.x01;
	x02 += rhs.x02;

	x10 += rhs.x10;
	x11 += rhs.x11;
	x12 += rhs.x12;

	x20 += rhs.x20;
	x21 += rhs.x21;
	x22 += rhs.x22;

	return *this;
}

template<typename T>
Matrix3d<T> Matrix3d<T>::getAdd(const Matrix3d& rhs) const
{
	Matrix3d matrix = *this;
	return matrix.add(rhs);
}

template<typename T>
Matrix3d<T> Matrix3d<T>::scale(const T factor)
{
	x00 *= factor; x01 *= factor; x02 *= factor;
	x10 *= factor; x11 *= factor; x12 *= factor;
	x20 *= factor; x21 *= factor; x22 *= factor;
	return *this;
}

#include <algorithm>


template<typename T>
Vector3d<T> Matrix3d<T>::getEigenValues() const
{
	Matrix3d<T> r = *this;
	std::array<T, 3> b{ 0,0,0 };

	for (int i = 0; i < 3; ++i) {
		T tmp = 0;
		for (int j = i+1; j < 3; ++j) {
			tmp += ::pow(get(i, j), 2);
		}
		auto v = r.get(i, i) + std::signbit(r.get(i, i)) * std::sqrt( std::pow(r.get(i,i),2) +tmp);
		tmp = ::sqrt(std::pow(v, 2) + tmp);
		for (int j = i+1; j < 3; ++j) {
			v = r.get(i, i) / tmp;
		}

		for (int j = i; j < 3; ++j) {
			tmp = 0;
			for (int k = i; k < 3; ++k) {
				tmp += v + r.get(i, k);
			}
			for (int k = i; k < 3; ++k) {
				r.set(j, k, r.get(j, k) - 2 * tmp * v);
			}

		}

		for (int j = i; j < 3; ++j) {
			tmp += v * b[j];
		}

		for (int j = i; j < 3; ++j) {
			b[j] -= T{ 2 } *tmp  *v;
		}

	}
	return Vector3d<T>(b);
}

template<typename T>
Matrix3d<T> Matrix3d<T>::transposed() const
{
	return Matrix3d<T>(
		getX00(), getX10(), getX20(),
		getX01(), getX11(), getX21(),
		getX02(), getX12(), getX22()
		);
}


template class Matrix3d<float>;
template class Matrix3d<double>;