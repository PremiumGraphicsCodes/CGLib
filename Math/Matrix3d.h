#ifndef __CRYSTAL_MATH_MATRIX_3D_H_
#define __CRYSTAL_MATH_MATRIX_3D_H_

#include "Tolerance.h"

#include <vector>
#include <cassert>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename>
		class Vector3d;
		template<typename>
		class Quaternion;

template<typename T>
class Matrix3d final
{
public:
	Matrix3d(void);

	Matrix3d(
		const T x00, const T x01, const T x02,
		const T x10, const T x11, const T x12,
		const T x20, const T x21, const T x22
		);

	explicit Matrix3d(const std::array<T, 9>& v);

	~Matrix3d() = default;

	void setIdentity() { *this = Identity(); }

	void setRotateX(const T angle) { *this = RotateX(angle); }

	void setRotateY(const T angle) { *this = RotateY(angle); }

	void setRotateZ(const T angle) { *this = RotateZ(angle); }

	static Matrix3d Identity() { return Matrix3d(1, 0, 0, 0, 1, 0, 0, 0, 1); }

	static Matrix3d Zero() { return Matrix3d(0, 0, 0, 0, 0, 0, 0, 0, 0); }

	static Matrix3d RotateX(const T angle) { return Matrix3d(1, 0, 0, 0, ::cos(angle), -::sin(angle), 0, ::sin(angle), ::cos(angle)); }

	static Matrix3d RotateY(const T angle) { return Matrix3d(::cos(angle), 0, ::sin(angle), 0, 1, 0, -::sin(angle), 0.0f, ::cos(angle)); }

	static Matrix3d RotateZ(const T angle) { return Matrix3d(::cos(angle), -::sin(angle), 0.0f,::sin(angle), ::cos(angle), 0.0f, 0.0f, 0.0f, 1.0f ); }

	bool isZero() const { return equals(Zero()); }

	bool isIdentity() const { return equals(Identity()); }

	bool equals(const Matrix3d& rhs) const;

	T getDeterminant() const;

	bool isRegular() const;

	Matrix3d getInverse() const;

	Matrix3d product(const Matrix3d& rhs) { return *this = getProduct(rhs); }

	Matrix3d getProduct(const Matrix3d& rhs) const;

	Matrix3d scale(const T factor);

	Matrix3d getScaled(const T factor) const {
		Matrix3d matrix = *this;
		return matrix.scale(factor);
	}

	Matrix3d transposed() const;

	Matrix3d add(const Matrix3d& rhs);

	Matrix3d getAdd(const Matrix3d& rhs) const;

	bool operator==(const Matrix3d& rhs) const { return this->equals(rhs); }

	Matrix3d operator+(const Matrix3d& rhs) const { return getAdd(rhs); }

	const Matrix3d operator+=(const Matrix3d& rhs) { return add(rhs); }

	Matrix3d operator-(const Matrix3d& rhs) const { return getAdd(rhs.getScaled(-1)); }

	const Matrix3d operator-=(const Matrix3d& rhs) { return add(rhs.getScaled(-1)); }

	Matrix3d operator*(const Matrix3d& rhs) const { return getProduct(rhs); }

	const Matrix3d operator*=(const Matrix3d& rhs) { return product(rhs); }

	void setX00(const T x) { this->x00 = x; }

	void setX01(const T x) { this->x01 = x; }

	void setX02(const T x) { this->x02 = x; }

	void setX10(const T x) { this->x10 = x; }

	void setX11(const T x) { this->x11 = x; }

	void setX12(const T x) { this->x12 = x; }

	void setX20(const T x) { this->x20 = x; }

	void setX21(const T x) { this->x21 = x; }

	void setX22(const T x) { this->x22 = x; }

	T getX00() const { return x00; }

	T getX01() const { return x01; }

	T getX02() const { return x02; }

	T getX10() const { return x10; }

	T getX11() const { return x11; }

	T getX12() const { return x12; }

	T getX20() const { return x20; }

	T getX21() const { return x21; }

	T getX22() const { return x22; }

	T get(const int i, const int j) const;

	void set(const int i, const int j, const T value);

	std::array<T, 9> toArray3x3() const;

	std::vector< T > toArray4x4() const;

	Vector3d<T> getEigenValues() const;

	Quaternion<T> toQuaternion() const;

	Vector3d<T> getRowVector(const int i) const;

	Vector3d<T> getColumnVector(const int j) const;

private:
	T x00, x01, x02;
	T x10, x11, x12;
	T x20, x21, x22;
};

	}
}

#endif