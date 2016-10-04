#include "gtest\gtest.h"
#include "../Math/JacobiSolver.h"
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

TEST(JacobiSolverTest, Test)
{
	Matrix<3, 3, double> matrix;
	matrix.set(0, 0, 1);
	matrix.set(1, 1, 1);
	matrix.set(2, 2, 1);
	JacobiSolver<3,3,double> solver(matrix);
	const auto& actual = solver.solve(1.0e-6);
	EXPECT_DOUBLE_EQ(actual[0], 1.0);
	EXPECT_DOUBLE_EQ(actual[1], 1.0);
	EXPECT_DOUBLE_EQ(actual[2], 1.0);
}


TEST(JacobiSolverTest, TestSymmetric)
{
	using TypeParam = double;
	Matrix<3, 3, TypeParam> m({ 1,0,1,0,1,-1,1,-1,0 });
	JacobiSolver<3, 3, TypeParam> solver(m);

	auto actual = solver.solve(0.0000001);
	EXPECT_TRUE(Tolerance<TypeParam>::isEqualLoosely(2.0, actual[0]));
	EXPECT_TRUE(Tolerance<TypeParam>::isEqualLoosely(1.0, actual[1]));
	EXPECT_TRUE(Tolerance<TypeParam>::isEqualLoosely(-1.0, actual[2]));

	auto p = solver.getOrthogonalMatrix();

	Matrix3d<TypeParam> m1(p.a);
	Matrix3d<TypeParam> m2(m.a);
	auto m3 = m1.getInverse();

	auto pap = m3 * m2 * m1;

	Matrix3d<TypeParam> expected(2, 0, 0, 0, 1, 0, 0, 0, -1);
	EXPECT_EQ(expected, pap);
}