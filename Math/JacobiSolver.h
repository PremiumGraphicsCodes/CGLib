#ifndef __CRYSTAL_MATH_JACOBI_SOLVER_H__
#define __CRYSTAL_MATH_JACOBI_SOLVER_H__

#include "Matrix.h"

namespace Crystal {
	namespace Math {

template<typename int ROW, typename int COLUMN, typename T>
class JacobiSolver
{
public:
	JacobiSolver(const Matrix<ROW, COLUMN, T>& matrix) :
		diagonalMatrix(matrix)
	{}

	T getMaxvalue(int *p, int *q)
	{
		T max = fabs(diagonalMatrix.get(0, 1));
		*p = 0;
		*q = 1;

		for (int i = 0; i < diagonalMatrix.getRow(); i++) {
			for (int j = i + 1; j < diagonalMatrix.getColumn(); j++) {
				T temp = fabs(diagonalMatrix.get(i, j));

				if (temp > max) {
					max = temp;
					*p = i;
					*q = j;
				}
			}
		}

		return max;
	}

	Vector<ROW, T> solve(const T eps, const int maxIter = 100) {
		T max;
		int p;
		int q;
		int iter = 0;
		do {
			iter++;
			if (!(max = getMaxvalue(&p, &q))) {
				break;
			}
			T app = diagonalMatrix.get(p, p);
			T apq = diagonalMatrix.get(p, q);
			T aqq = diagonalMatrix.get(q, q);

			T alpha = (app - aqq) / T{ 2 };
			T beta = -apq;
			T gamma = fabs(alpha) / sqrt(alpha*alpha + beta * beta);

			T s = sqrt((T{ 1 } -gamma) / T{ 2 });
			T c = sqrt((T{ 1 } +gamma) / T{ 2 });
			if (alpha * beta < 0.0) {
				s = -s;
			}

			for (int i = 0; i < ROW; ++i) {
				T tmp = c * diagonalMatrix.get(p, i) - s * diagonalMatrix.get(q, i);
				diagonalMatrix.set(q, i, s * diagonalMatrix.get(p, i) + c * diagonalMatrix.get(q, i));
				diagonalMatrix.set(p, i, tmp);
			}

			for (int i = 0; i < ROW; ++i) {
				diagonalMatrix.set(i, p, diagonalMatrix.get(p, i));
				diagonalMatrix.set(i, q, diagonalMatrix.get(q, i));
			}

			diagonalMatrix.set(p, p, c*c*app + s*s*aqq - 2 * s*c*apq);
			diagonalMatrix.set(p, q, s*c*(app - aqq) + (c*c - s*s)*apq);
			diagonalMatrix.set(q, p, s*c*(app - aqq) + (c*c - s*s)*apq);
			diagonalMatrix.set(q, q, s*s*app + c*c*aqq + 2 * s*c*apq);

			for (int i = 0; i < ROW; ++i) {
				T tmp = c * orthogonalMatrix.get(i, p) - s*orthogonalMatrix.get(i, q);
				orthogonalMatrix.set(i, q, s*orthogonalMatrix.get(i, p) + c * orthogonalMatrix.get(i, q));
				orthogonalMatrix.set(i, p, tmp);
			}
		} while (max >= eps && iter < maxIter);
		Vector<ROW, T> v;
		for (int i = 0; i < ROW; ++i) {
			v.set(i, diagonalMatrix.get(i, i));
		}
		return v;
	}

	Matrix<ROW, COLUMN, T> getOrthogonalMatrix() const { return orthogonalMatrix; }

	Matrix<ROW, COLUMN, T> getDiagonalMatrix() const { return diagonalMatrix; }

private:
	Matrix<ROW, COLUMN, T> diagonalMatrix;
	Matrix<ROW, COLUMN, T> orthogonalMatrix;
};

	}
}

#endif