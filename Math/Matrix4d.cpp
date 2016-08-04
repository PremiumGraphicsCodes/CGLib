#include "Matrix4d.h"
#include "Vector3d.h"
#include "Vector4d.h"

using namespace Crystal::Math;

template<typename T>
Matrix4d<T>::Matrix4d(void)
{
	x[0] = 1.0;		x[1] = 0.0;		x[2] = 0.0;		x[3] = 0.0;
	x[4] = 0.0;		x[5] = 1.0;		x[6] = 0.0;		x[7] = 0.0;
	x[8] = 0.0;		x[9] = 0.0;		x[10] = 1.0;	x[11] = 0.0;
	x[12] = 0.0;	x[13] = 0.0;	x[14] = 0.0;	x[15] = 1.0;
}

template<typename T>
Matrix4d<T>::Matrix4d(
	const T x00, const T x01, const T x02, const T x03,
	const T x10, const T x11, const T x12, const T x13,
	const T x20, const T x21, const T x22, const T x23,
	const T x30, const T x31, const T x32, const T x33
	)
{
	x[0] = x00;		x[1] = x01;		x[2] = x02;		x[3] = x03;
	x[4] = x10;		x[5] = x11;		x[6] = x12;		x[7] = x13;
	x[8] = x20;		x[9] = x21;		x[10] = x22;	x[11] = x23;
	x[12] = x30;	x[13] = x31;	x[14] = x32;	x[15] = x33;
}

template<typename T>
Matrix4d<T>::Matrix4d(const Matrix3d<T>& m)
{
	x[0] = m.getX00();	x[1] = m.getX01();	x[2] = m.getX02();	x[3] = 0;
	x[4] = m.getX10();	x[5] = m.getX11();	x[6] = m.getX12();	x[7] = 0;
	x[8] = m.getX20();	x[9] = m.getX21();	x[10] = m.getX22();	x[11] = 0;
	x[12] = 0;	x[13] = 0;			x[14] = 0;			x[15] = 1;
}

template<typename T>
Matrix4d<T> Matrix4d<T>::Zero() {
	return Matrix4d<T>
	(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	);
}


template<typename T>
void Matrix4d<T>::multiple(const Matrix4d<T>& rhs)
{
	T y[16];
	for (int i = 0; i < 4; ++i) {
		y[0 + i] = x[0 + i] * rhs.x[0] + x[4 + i] * rhs.x[1] + x[8 + i] * rhs.x[2] + x[12 + i] * rhs.x[3];
		y[4 + i] = x[0 + i] * rhs.x[4] + x[4 + i] * rhs.x[5] + x[8 + i] * rhs.x[6] + x[12 + i] * rhs.x[7];
		y[8 + i] = x[0 + i] * rhs.x[8] + x[4 + i] * rhs.x[9] + x[8 + i] * rhs.x[10] + x[12 + i] * rhs.x[11];
		y[12 + i] = x[0 + i] * rhs.x[12] + x[4 + i] * rhs.x[13] + x[8 + i] * rhs.x[14] + x[12 + i] * rhs.x[15];
	}
	for (int i = 0; i < 16; ++i) {
		this->x[i] = y[i];
	}
}

template<typename T>
bool Matrix4d<T>::equals(const Matrix4d<T>& rhs) const {
	for (int i = 0; i < 16; ++i) {
		if (!Tolerance<T>::isEqualLoosely(x[i], rhs.x[i])) {
			return false;
		}
	}
	return true;
}

template<typename T>
Vector3d<T> Matrix4d<T>::multiple(const Vector3d<T>& v)
{
	const auto x = getX00() * v.getX() + getX01() * v.getY() + getX02() * v.getZ() + getX03() * 1.0f;
	const auto y = getX10() * v.getX() + getX11() * v.getY() + getX12() * v.getZ() + getX13() * 1.0f;
	const auto z = getX20() * v.getX() + getX21() * v.getY() + getX22() * v.getZ() + getX23() * 1.0f;
	const auto w = getX30() * v.getX() + getX31() * v.getY() + getX23() * v.getZ() + getX33() * 1.0f;
	return Vector3d<T>(x/w, y/w, z/w);
}

template<typename T>
Vector4d<T> Matrix4d<T>::multiple(const Vector4d<T>& v)
{
	const auto xx = getX00() * v.getX() + getX01() * v.getY() + getX02() * v.getZ() + getX03() * v.getW();
	const auto yy = getX10() * v.getX() + getX11() * v.getY() + getX12() * v.getZ() + getX13() * v.getW();
	const auto zz = getX20() * v.getX() + getX21() * v.getY() + getX22() * v.getZ() + getX23() * v.getW();
	const auto ww = getX30() * v.getX() + getX31() * v.getY() + getX23() * v.getZ() + getX33() * v.getW();
	return Vector4d<T>(xx, yy,zz,ww);
}


template<typename T>
Matrix4d<T> Matrix4d<T>::transposed() const
{
	return Matrix4d<T>(
		getX00(), getX10(), getX20(), getX30(),
		getX01(), getX11(), getX21(), getX31(),
		getX02(), getX12(), getX22(), getX32(),
		getX03(), getX13(), getX23(), getX33()
		);
}

template<typename T>
void Matrix4d<T>::translate(const T x, const T y, const T z)
{
	Matrix4d m;
	m.x[12] = x;
	m.x[13] = y;
	m.x[14] = z;
	(*this) *= m;
}

template<typename T>
void Matrix4d<T>::setScale(const T x, const T y, const T z)
{
	this->x[0] = x;
	this->x[5] = y;
	this->x[10] = z;
}

template<typename T>
T Matrix4d<T>::getDeterminent() const
{
	const auto a11 = getX00(); const auto a12 = getX01(); const auto a13 = getX02(); const auto a14 = getX03();
	const auto a21 = getX10(); const auto a22 = getX11(); const auto a23 = getX12(); const auto a24 = getX13();
	const auto a31 = getX20(); const auto a32 = getX21(); const auto a33 = getX22(); const auto a34 = getX23();
	const auto a41 = getX30(); const auto a42 = getX31(); const auto a43 = getX32(); const auto a44 = getX33();

	return
		(a11 * a22 * a33 * a44) + (a11 * a23 * a34 * a42) + (a11 * a24 * a32 * a43) +
		(a12 * a21 * a34 * a43) + (a12 * a23 * a31 * a44) + (a12 * a24 * a33 * a41) +
		(a13 * a21 * a32 * a44) + (a13 * a22 * a34 * a41) + (a13 * a24 * a31 * a42) +
		(a14 * a21 * a33 * a42) + (a14 * a22 * a31 * a43) + (a14 * a23 * a32 * a41) -
		(a11 * a22 * a34 * a43) - (a11 * a23 * a32 * a44) - (a11 * a24 * a33 * a42) -
		(a12 * a21 * a33 * a44) - (a12 * a23 * a34 * a41) - (a12 * a24 * a31 * a43) -
		(a13 * a21 * a34 * a42) - (a13 * a22 * a31 * a44) - (a13 * a24 * a32 * a41) -
		(a14 * a21 * a32 * a43) - (a14 * a22 * a33 * a41) - (a14 * a23 * a31 * a42);
}


template class Matrix4d<float>;
template class Matrix4d<double>;