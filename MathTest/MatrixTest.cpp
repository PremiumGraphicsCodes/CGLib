#include "gtest\gtest.h"
#include "../Math/Matrix.h"
#include "../Math/Tolerance.h"

#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

TEST(MatrixTest, Test)
{
	Matrix<3, 3> m;

	m.a[0 * m.getRow() + 0] = 0.0;
	m.a[0 * m.getRow() + 1] = 2.0;
	m.a[0 * m.getRow() + 2] = 2.0;

	m.a[1 * m.getRow() + 0] = 2.0;
	m.a[1 * m.getRow() + 1] = 1.0;
	m.a[1 * m.getRow() + 2] = 0.0;

	m.a[2 * m.getRow() + 0] = 2.0;
	m.a[2 * m.getRow() + 1] = 0.0;
	m.a[2 * m.getRow() + 2] = -1.0;

	const auto q = m.qrDecomposition(0.0000001);
	EXPECT_FLOAT_EQ(-3, m.a[0]);
	EXPECT_FLOAT_EQ(3, m.a[4]);
	EXPECT_TRUE( Tolerance<float>::isEqualLoosely( 0.0, m.a[8]) );

	Matrix3d<double> m1(q.a);
	Matrix3d<double> m2(m.a[4], 0, 0, 0, m.a[8], 0, 0, 0, m.a[0]);
	Matrix3d<double> m3 = m1.transposed();
	auto a = m3 * m2 * m1;
}