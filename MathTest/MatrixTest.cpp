#include "gtest\gtest.h"
#include "../Math/Matrix.h"
#include "../Math/Tolerance.h"

#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

/*
TEST(MatrixTest, TestSolveSimulateneousEquation)
{
	Matrix<3, 3, double> m({ 1,2,0,2,4,2,5,7,3 });
	Vector<3> b({ -5,-4,10 });
	auto result = m.solveSimulateneousEquation(b);
}
*/

TEST(MatrixTest, Test)
{
	Matrix<3, 3, double> m({ 0,2,2,2,1,0,2,0,-1 });

	const auto q = m.qrDecomposition(0.0000001);
	EXPECT_TRUE( Tolerance<double>::isEqualLoosely(-3.0, m.a[0]) );
	EXPECT_TRUE( Tolerance<double>::isEqualLoosely( 3.0, m.a[4]) );
	EXPECT_TRUE( Tolerance<double>::isEqualLoosely( 0.0, m.a[8]) );
	m.clear(0.001);

	Vector<3> v1(std::array<double,3>{1, 0, 0});
	auto result1 = m.solveSimulateneousEquation(v1);
	Vector<3> v2(std::array<double, 3>{0, 1, 0});
	auto result2 = m.solveSimulateneousEquation(v2);
	Vector<3> v3(std::array<double, 3>{0, 0, 1});
	auto result3 = m.solveSimulateneousEquation(v3);


	Matrix3d<double> m1(q.a);
	Matrix3d<double> m2(m.a[4], 0, 0, 0, m.a[8], 0, 0, 0, m.a[0]);
	Matrix3d<double> m3 = m1.transposed();
	auto a = m3 * m2 * m1;
}