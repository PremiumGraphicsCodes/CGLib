#include "gtest\gtest.h"
#include "../Math/JacobiSolver.h"
#include "../Math/Matrix2d.h"
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

TEST(JacobiSolverTest, TestGetDiagonalMatrix2x2)
{
	using T = double;
	Matrix<2, 2, T> m({ 1,2,2,1 });
	JacobiSolver<2, 2, T> solver(m);

	solver.solve(1.0e-6);

	const auto& actual = solver.getDiagonalMatrix();
	const Matrix<2, 2, T> expected({ -1, 0, 0, 3 });
	EXPECT_EQ(expected, actual);
}

TEST(JacobiSolverTest, TestGetDiagonalMatrix3x3)
{
	using T = double;
	Matrix<3, 3, T> m({ 1,0,1,0,1,-1,1,-1,0 });
	JacobiSolver<3, 3, T> solver(m);

	solver.solve(1.0e-6);

	const auto& actual = solver.getDiagonalMatrix();
	Matrix<3, 3, T> expected({ 2, 0, 0, 0, 1, 0, 0, 0, -1 });
	EXPECT_EQ(expected, actual);
}


TEST(JacobiSolverTest, TestSolve2x2)
{
	using T = double;
	Matrix<2, 2, T> m({ 1,2,2,1 });
	JacobiSolver<2, 2, T> solver(m);

	solver.solve(1.0e-6);

	const auto& p = solver.getOrthogonalMatrix();

	Matrix2d<T> m1(p.a);
	Matrix2d<T> m2(m.a);
	auto m3 = m1.getInverse();

	auto pap = m3 * m2 * m1;

	Matrix2d<T> expected({ -1, 0, 0, 3 });
	EXPECT_EQ(expected, pap);
}

TEST(JacobiSolverTest, TestSolve3x3)
{
	using T = double;
	Matrix<3, 3, T> m({ 1,0,1,0,1,-1,1,-1,0 });
	JacobiSolver<3, 3, T> solver(m);

	const auto& actual = solver.solve(1.0e-6);
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(2.0, actual[0]));
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(1.0, actual[1]));
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(-1.0, actual[2]));

	const auto& p = solver.getOrthogonalMatrix();

	Matrix3d<T> m1(p.a);
	Matrix3d<T> m2(m.a);
	auto m3 = m1.getInverse();

	auto pap = m3 * m2 * m1;

	Matrix3d<T> expected(2, 0, 0, 0, 1, 0, 0, 0, -1);
	EXPECT_EQ(expected, pap);
}